#include "waifupch.h"
#include "Network.h"

WaifuCPU::Network::Network(size_t inputSize, size_t encoderLayersCount, size_t latentSpaceNeuronAmount)
{
    m_InputSize = inputSize;

    m_RedChannelError   = 0.0f;
    m_GreenChannelError = 0.0f;
    m_BlueChannelError  = 0.0f;

    m_AverageRedChannelError    = 0.0f;
    m_AverageGreenChannelError  = 0.0f;
    m_AverageBlueChannelError   = 0.0f;

    // Encoder

    size_t neuronCount = inputSize + 1;
    for (size_t i{}; i < encoderLayersCount; i++) {
        m_HiddenLayers.push_back(Layer());

        for (size_t j{}; j < neuronCount; j++) {
            m_HiddenLayers.back().push_back(Neuron(neuronCount, j));
        }

        m_HiddenLayers.back().back().setOutputValue(PixelRGB(1.0f, 1.0f, 1.0f));
    }

    // Latent space

    m_HiddenLayers.push_back(Layer());
    for (size_t i{}; i < latentSpaceNeuronAmount; i++) {
        m_HiddenLayers.back().push_back(Neuron(neuronCount, i));
    }

    m_HiddenLayers.back().back().setOutputValue(PixelRGB(1.0f, 1.0f, 1.0f));

    // Decoder

    m_HiddenLayers.push_back(Layer());
    for (size_t i{}; i < neuronCount; i++) {
        m_HiddenLayers.back().push_back(Neuron(latentSpaceNeuronAmount, i));
    }

    m_HiddenLayers.back().back().setOutputValue(PixelRGB(1.0f, 1.0f, 1.0f));

    for (size_t i{}; i < encoderLayersCount - 1; i++) {
        m_HiddenLayers.push_back(Layer());

        for (size_t j{}; j < neuronCount; j++) {
            m_HiddenLayers.back().push_back(Neuron(neuronCount, j));
        }
    }

    m_HiddenLayers.back().back().setOutputValue(PixelRGB(1.0f, 1.0f, 1.0f));
}

void _WF_CALL Network::feedForward(const std::vector<PixelRGB>& inputValues)
{
    assert(inputValues.size() == m_InputSize);

    for (size_t i{}; i < inputValues.size(); i++) {
        m_HiddenLayers[0][i].setOutputValue(inputValues[i]);
        size_t z = 0;
    }

    for (size_t i = 1; i < m_HiddenLayers.size(); ++i) {
        Layer& prevLayer = m_HiddenLayers[i - 1];

        for (size_t j{}; j < m_HiddenLayers[i].size() - 1; ++j) {
            m_HiddenLayers[i][j].feedForward(prevLayer);
        }
        std::cout << "debug: " << prevLayer.size() << "\n";
    }

    //this->sendToOutput();
}

void _WF_CALL Network::backPropagate(const std::vector<PixelRGB>& targetValues)
{
    Layer& outputLayer = m_HiddenLayers.back();

    m_RedChannelError   = 0.0f;
    m_GreenChannelError = 0.0f;
    m_BlueChannelError  = 0.0f;

    for (size_t i{}; i < outputLayer.size() - 1; i++) {
        double deltaRed     = targetValues[i][0] - outputLayer[i].getOutputValue()[0];
        double deltaGreen   = targetValues[i][1] - outputLayer[i].getOutputValue()[1];
        double deltaBlue    = targetValues[i][2] - outputLayer[i].getOutputValue()[2];

        m_RedChannelError   += deltaRed * deltaRed;
        m_GreenChannelError += deltaGreen * deltaGreen;
        m_BlueChannelError  += deltaBlue * deltaBlue;
    }

    m_RedChannelError /= outputLayer.size() - 1;
    m_RedChannelError = sqrt(m_RedChannelError);

    m_GreenChannelError /= outputLayer.size() - 1;
    m_GreenChannelError = sqrt(m_GreenChannelError);

    m_BlueChannelError /= outputLayer.size() - 1;
    m_BlueChannelError = sqrt(m_BlueChannelError);

    m_AverageRedChannelError    = (m_AverageRedChannelError * C_SMOOTH_FACTOR + m_RedChannelError) / (C_SMOOTH_FACTOR + 1.0f);
    m_AverageGreenChannelError  = (m_AverageGreenChannelError * C_SMOOTH_FACTOR + m_GreenChannelError) / (C_SMOOTH_FACTOR + 1.0f);
    m_AverageBlueChannelError    = (m_AverageBlueChannelError * C_SMOOTH_FACTOR + m_BlueChannelError) / (C_SMOOTH_FACTOR + 1.0f);

    for (size_t i{}; i < outputLayer.size() - 1; ++i) {
        outputLayer[i].calcOutputGradient(targetValues[i]);
    }

    for (size_t i = m_HiddenLayers.size() - 2; i > 0; --i) {
        Layer& hiddenLayer = m_HiddenLayers[i];
        Layer& nextLayer = m_HiddenLayers[i + 1];

        for (size_t j{}; j < hiddenLayer.size(); ++j) {
            hiddenLayer[i].calcHiddenGradient(nextLayer);
        }
    }

    for (size_t i = m_HiddenLayers.size() - 1; i > 0; --i) {
        Layer& layer = m_HiddenLayers[i];
        Layer& prevLayer = m_HiddenLayers[i - 1];

        for (size_t j{}; j < layer.size() - 1; j++) {
            layer[j].updateWeights(prevLayer);
        }
    }

    // Set output

    this->sendToOutput();
}

void _WF_CALL Network::saveConfiguration()
{
    /*std::string name = "config.txt";
    std::ofstream conFile(name);

    for (size_t i{}; i < m_HiddenLayers.size(); i++) {
        for (size_t j{}; j < m_HiddenLayers[i].size(); j++) {
            conFile << "m_RedWeight: " << m_HiddenLayers[i][j].
        }
    }*/
}

void _WF_CALL Network::sendToOutput()
{
    Layer& out = m_HiddenLayers.back();
    for (size_t i{}; i < out.size() - 1; i++) {
        m_Output.push_back(out[i].getOutputValue());
    }
}