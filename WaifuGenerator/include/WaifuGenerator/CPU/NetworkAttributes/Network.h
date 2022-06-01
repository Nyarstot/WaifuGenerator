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
#ifndef CPU_WAIFUGENERATOR_NETWORK_H
#define CPU_WAIFUGENERATOR_NETWORK_H

#include <WaifuGenerator/CPU/ImageUtils/PixelRGB.h>
#include <WaifuGenerator/CPU/NetworkAttributes/Core.h>
#include <WaifuGenerator/CPU/NetworkAttributes/Neuron.h>

_WF_BEGIN

class Network
{
    typedef std::vector<Neuron> Layer;

private:
    std::vector<PixelRGB> m_Output;
    std::vector<Layer> m_HiddenLayers;

    size_t m_InputSize;
    size_t m_EncoderLayersAmount;
    size_t m_LatentLayerSize;

    double m_RedChannelError;
    double m_GreenChannelError;
    double m_BlueChannelError;

    double m_AverageRedChannelError;
    double m_AverageGreenChannelError;
    double m_AverageBlueChannelError;

private:
    void sendToOutput();

public:
    Network(size_t inputSize, size_t encoderLayersCount, size_t latentSpaceNeuronAmount);

    void feedForward(const std::vector<PixelRGB>& inputValues);
    void backPropagate(const std::vector<PixelRGB>& targetValues);

    void saveConfiguration();
    void readConfiguration(std::string path);

    std::vector<PixelRGB> getResult()    const { return m_Output; }
    double getAverageRedChannelError()   const { return m_AverageRedChannelError; }
    double getAverageGreenChannelError() const { return m_AverageGreenChannelError; }
    double getAverageBlueChannelError()  const { return m_AverageBlueChannelError; }

};

_WF_END

#endif // !CPU_WAIFUGENERATOR_NETWORK_H

