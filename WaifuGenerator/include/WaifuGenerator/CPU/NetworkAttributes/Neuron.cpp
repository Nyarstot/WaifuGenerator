#include "waifupch.h"
#include "Neuron.h"

WaifuCPU::Neuron::Neuron(size_t outputAmount, size_t neuronIndex)
{
    for (size_t i{}; i < outputAmount; i++) {
        m_OutputWeights.push_back(Connector());

        m_OutputWeights.back().m_RedWeight   = this->randomizeWeight();
        m_OutputWeights.back().m_GreenWeight = this->randomizeWeight();
        m_OutputWeights.back().m_BlueWeight  = this->randomizeWeight();
    }

    m_NeuronIndex = neuronIndex;
}

double _WF_CALL Neuron::randomizeWeight()
{
    return rand() / double(RAND_MAX);
}

_WF_CALL PixelRGB _WF_CALL Neuron::activationFunction(PixelRGB value)
{
    double tanhRed   = tanh(value[0]);
    double tanhGreen = tanh(value[1]);
    double tanhBlue  = tanh(value[2]);

    return PixelRGB(tanhRed, tanhGreen, tanhBlue);
}

_WF_CALL PixelRGB _WF_CALL Neuron::activationFunctionDerivative(PixelRGB value)
{
    double drvtRed   = 1 / pow(cosh(value[0]), 2);
    double drvtGreen = 1 / pow(cosh(value[1]), 2);
    double drvtBlue  = 1 / pow(cosh(value[2]), 2);

    return PixelRGB(drvtRed, drvtGreen, drvtBlue);
}

_WF_CALL PixelRGB _WF_CALL Neuron::sumDOW(const std::vector<Neuron>& nextLayer)
{
    double sumRed   = 0.0f;
    double sumGreen = 0.0f;
    double sumBlue  = 0.0f;

    if (nextLayer.size() == m_OutputWeights.size()) {
        for (size_t i{}; i < nextLayer.size() - 1; i++) {
            sumRed   += m_OutputWeights[i].m_RedWeight * nextLayer[m_NeuronIndex].m_RedGradient;
            sumGreen += m_OutputWeights[i].m_GreenWeight * nextLayer[m_NeuronIndex].m_GreenGradient;
            sumBlue  += m_OutputWeights[i].m_BlueWeight * nextLayer[m_NeuronIndex].m_BlueGradient;
        }
    }

    if (nextLayer.size() != m_OutputWeights.size()) {
        for (size_t i{}; i < m_OutputWeights.size() - 1; i++) {
            for (size_t j{}; j < nextLayer.size() - 1; j++) {
                sumRed   += m_OutputWeights[i].m_RedWeight * nextLayer[j].m_RedGradient;
                sumGreen += m_OutputWeights[i].m_RedWeight * nextLayer[j].m_GreenGradient;
                sumBlue  += m_OutputWeights[i].m_RedWeight * nextLayer[j].m_BlueGradient;
            }
        }
    }

    return PixelRGB(sumRed, sumGreen, sumBlue);
}

void _WF_CALL Neuron::feedForward(const std::vector<Neuron>& prevLayer)
{
    double sumRed   = 0.0f;
    double sumGreen = 0.0f;
    double sumBlue  = 0.0f;

    for (size_t i{}; i < prevLayer.size(); i++) {
        sumRed = prevLayer[i].getOutputValue()[0] * prevLayer[i].m_OutputWeights[m_NeuronIndex].m_RedWeight;
        sumGreen = prevLayer[i].getOutputValue()[1] * prevLayer[i].m_OutputWeights[m_NeuronIndex].m_GreenWeight;
        sumBlue = prevLayer[i].getOutputValue()[2] * prevLayer[i].m_OutputWeights[m_NeuronIndex].m_BlueWeight;
    }

    m_OutputValue = this->activationFunction(PixelRGB(sumRed, sumGreen, sumBlue));
}

void _WF_CALL Neuron::calcOutputGradient(PixelRGB targetValues)
{
    double deltaRed   = targetValues[0] - m_OutputValue[0];
    double deltaGreen = targetValues[1] - m_OutputValue[1];
    double deltaBlue  = targetValues[2] - m_OutputValue[2];

    PixelRGB drvtRGB = this->activationFunctionDerivative(PixelRGB(deltaRed, deltaGreen, deltaBlue));

    m_RedGradient   = deltaRed * drvtRGB[0];
    m_GreenGradient = deltaGreen * drvtRGB[1];
    m_BlueGradient  = deltaBlue * drvtRGB[2];
}

void _WF_CALL Neuron::calcHiddenGradient(const std::vector<Neuron>& nextLayer)
{
    PixelRGB dow = sumDOW(nextLayer);
    PixelRGB outDerivative = this->activationFunctionDerivative(m_OutputValue);

    m_RedGradient   = dow[0] * outDerivative[0];
    m_GreenGradient = dow[1] * outDerivative[1];
    m_BlueGradient  = dow[2] * outDerivative[2];
}

void _WF_CALL Neuron::updateWeights(std::vector<Neuron>& prevLayer)
{
    for (size_t i{}; i < prevLayer.size(); ++i) {
        Neuron& l_Neuron = prevLayer[i];

        double oldDeltaRedWeight    = l_Neuron.m_OutputWeights[m_NeuronIndex].m_DeltaRedWeight;
        double oldDeltaGreenWeight  = l_Neuron.m_OutputWeights[m_NeuronIndex].m_DeltaGreenWeight;
        double oldDeltaBlueWeight   = l_Neuron.m_OutputWeights[m_NeuronIndex].m_DeltaBlueWeight;

        double newDeltaRedWeight    = C_ETA * l_Neuron.getOutputValue()[0] * m_RedGradient + C_ALPHA * oldDeltaRedWeight;
        double newDeltaGreenWeight  = C_ETA * l_Neuron.getOutputValue()[1] * m_GreenGradient + C_ALPHA * oldDeltaGreenWeight;
        double newDeltaBlueWeight   = C_ETA * l_Neuron.getOutputValue()[2] * m_BlueGradient + C_ALPHA * oldDeltaBlueWeight;

        // Set to neuron

        l_Neuron.m_OutputWeights[m_NeuronIndex].m_DeltaRedWeight = newDeltaRedWeight;
        l_Neuron.m_OutputWeights[m_NeuronIndex].m_RedWeight += newDeltaRedWeight;

        l_Neuron.m_OutputWeights[m_NeuronIndex].m_DeltaGreenWeight = newDeltaGreenWeight;
        l_Neuron.m_OutputWeights[m_NeuronIndex].m_GreenWeight += newDeltaBlueWeight;

        l_Neuron.m_OutputWeights[m_NeuronIndex].m_DeltaBlueWeight = newDeltaBlueWeight;
        l_Neuron.m_OutputWeights[m_NeuronIndex].m_BlueWeight += newDeltaBlueWeight;
    }
}


