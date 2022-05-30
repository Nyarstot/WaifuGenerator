#include "waifupch.h"
#include "PixelRGB.h"

WaifuCPU::PixelRGB::PixelRGB()
{
    //m_RGBChannels = (double*)::operator new(3 * sizeof(double));

    m_RGBChannels.push_back(0.0f);
    m_RGBChannels.push_back(0.0f);
    m_RGBChannels.push_back(0.0f);
}

WaifuCPU::PixelRGB::PixelRGB(const double& R, const double& G, const double& B)
{
    //m_RGBChannels = (double*)::operator new(3 * sizeof(double));

    m_RGBChannels.push_back(R);
    m_RGBChannels.push_back(G);
    m_RGBChannels.push_back(B);
}

WaifuCPU::PixelRGB::PixelRGB(const PixelRGB& buffer)
{
    m_RGBChannels = buffer.m_RGBChannels;
}
