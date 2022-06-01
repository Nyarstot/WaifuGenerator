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
#ifndef CPU_WAIFUGENERATOR_NEURON_H
#define CPU_WAIFUGENERATOR_NEURON_H

#include <WaifuGenerator/CPU/ImageUtils/PixelRGB.h>
#include <WaifuGenerator/CPU/NetworkAttributes/Core.h>

_WF_BEGIN

struct Connector
{
    double m_RedWeight;
    double m_GreenWeight;
    double m_BlueWeight;

    double m_DeltaRedWeight;
    double m_DeltaGreenWeight;
    double m_DeltaBlueWeight;
};

class Neuron
{
private:
    std::vector<Connector> m_OutputWeights;
    PixelRGB m_OutputValue;

    double m_RedGradient;
    double m_GreenGradient;
    double m_BlueGradient;

    size_t m_NeuronIndex;

private:
    double randomizeWeight();
    PixelRGB activationFunction(PixelRGB value);
    PixelRGB activationFunctionDerivative(PixelRGB value);
    PixelRGB sumDOW(const std::vector<Neuron>& nextLayer);

public:
    Neuron(size_t outputAmount, size_t neuronIndex);

    void feedForward(const std::vector<Neuron>& prevLayer);
    void calcOutputGradient(PixelRGB targetValues);
    void calcHiddenGradient(const std::vector<Neuron>& nextLayer);
    void updateWeights(std::vector<Neuron>& prevLayer);

    void setOutputValue(PixelRGB value) { m_OutputValue = std::move(value); }
    PixelRGB getOutputValue() const { return m_OutputValue; }

    double getRedWeight()   const { return m_OutputWeights[m_NeuronIndex].m_RedWeight; }
    double getGreenWeight() const { return m_OutputWeights[m_NeuronIndex].m_GreenWeight; }
    double getBlueWeight()  const { return m_OutputWeights[m_NeuronIndex].m_RedWeight; }

    double getDeltaRedWeight()  const { return m_OutputWeights[m_NeuronIndex].m_DeltaRedWeight; }
    double getDeltaGreenWeight() const { return m_OutputWeights[m_NeuronIndex].m_DeltaGreenWeight; }
    double getDeltaBlueWeight() const { return m_OutputWeights[m_NeuronIndex].m_DeltaBlueWeight; }

};

_WF_END

#endif // !CPU_WAIFUGENERATOR_NEURON_H


