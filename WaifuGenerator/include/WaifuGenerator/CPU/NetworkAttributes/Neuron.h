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

    void updateWeightsIfEqual(std::vector<Neuron>& prevLayer);
    void updateWeightsIfNotEqual(std::vector<Neuron>& prevLayer);

public:
    Neuron(size_t outputAmount, size_t neuronIndex);

    void feedForward(const std::vector<Neuron>& prevLayer);
    void calcOutputGradient(PixelRGB targetValues);
    void calcHiddenGradient(const std::vector<Neuron>& nextLayer);
    void updateWeights(std::vector<Neuron>& prevLayer);

    void setOutputValue(PixelRGB value) { m_OutputValue = std::move(value); }
    PixelRGB getOutputValue() const { return m_OutputValue; }
};

_WF_END

#endif // !CPU_WAIFUGENERATOR_NEURON_H

