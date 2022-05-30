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

    std::vector<PixelRGB> getResult()    const { return m_Output; }
    double getAverageRedChannelError()   const { return m_AverageRedChannelError; }
    double getAverageGreenChannelError() const { return m_AverageGreenChannelError; }
    double getAverageBlueChannelError()  const { return m_AverageBlueChannelError; }

};

_WF_END

#endif // !CPU_WAIFUGENERATOR_NETWORK_H

