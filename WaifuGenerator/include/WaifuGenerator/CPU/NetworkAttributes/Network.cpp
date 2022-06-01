// Author: Nikita Kozlov
// Link: github.com/nyarstot
//
// This file is part of WaifuGenerator neural network.
//
// WaifuGenerator is free software: you can redistribute it and/or modify
// it under terms of the GNU Generan Public License as published by
// the free software foundation, either version 3 of License, or
// (at your option) any later version.
//
// WaifuGenerator is distributed in the hope that it will be usefull,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with WaifuGenerator. If not, see <https://www.gnu.org/licenses/>.
#include "waifupch.h"
#include "Network.h"

#include <TinyXML/include/tinystr.h>
#include <TinyXML/include/tinyxml.h>

WaifuCPU::Network::Network(size_t inputSize, size_t encoderLayersCount, size_t latentSpaceNeuronAmount)
{
    m_InputSize = inputSize;
    m_EncoderLayersAmount = encoderLayersCount;
    m_LatentLayerSize = latentSpaceNeuronAmount;

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
    TiXmlDocument configDocument;

    TiXmlNode* root(configDocument.InsertEndChild(TiXmlElement("NetworkConfig")));
    TiXmlElement generalData("GeneralData");
    generalData.SetDoubleAttribute("InputSize", m_InputSize);
    generalData.SetDoubleAttribute("EncoderLayers", m_EncoderLayersAmount);
    generalData.SetDoubleAttribute("LatentVectorSize", m_LatentLayerSize);
    root->InsertEndChild(generalData);

    for (size_t i{}; i < m_HiddenLayers.size(); i++) {
        TiXmlElement weightData("WeightData");
        weightData.SetDoubleAttribute("LayerIndex", i);

        for (size_t j{}; j < m_HiddenLayers[i].size(); j++) {
            TiXmlElement weight("Weight");
            weight.SetDoubleAttribute("Index", j);
            weight.SetDoubleAttribute("RWeight", m_HiddenLayers[i][j].getRedWeight());
            weight.SetDoubleAttribute("GWeight", m_HiddenLayers[i][j].getGreenWeight());
            weight.SetDoubleAttribute("BWeight", m_HiddenLayers[i][j].getBlueWeight());
            weightData.InsertEndChild(weight);
        }

        root->InsertEndChild(weightData);
    }
    configDocument.SaveFile("NetConfig.xml");
}

void _WF_CALL Network::readConfiguration(std::string path)
{
    TiXmlDocument configDocumetn;

    if (configDocumetn.LoadFile(path)) {
        TiXmlElement* root = configDocumetn.RootElement();
        TiXmlElement* general = root->FirstChildElement();
        TiXmlElement* weightsData = general->NextSiblingElement();

        m_InputSize = std::stoi(general->Attribute("InputSize"));
        m_EncoderLayersAmount = std::stoi(general->Attribute("EncoderLayers"));
        m_LatentLayerSize = std::stoi(general->Attribute("LatentVectorSize"));

        while (weightsData != NULL) {
            TiXmlElement* currWeight = weightsData->FirstChildElement();
            size_t layerIndex = std::stoi(weightsData->Attribute("LayerIndex"));

            while (currWeight != NULL) {
                std::cout << currWeight->Attribute("Index") << "\n";
                currWeight = currWeight->NextSiblingElement();
            }

            weightsData = weightsData->NextSiblingElement();
        }
    }
    else {
        
    }
}

void _WF_CALL Network::sendToOutput()
{
    m_Output.clear();

    Layer& out = m_HiddenLayers.back();
    for (size_t i{}; i < out.size() - 1; i++) {
        m_Output.push_back(out[i].getOutputValue());
    }
}