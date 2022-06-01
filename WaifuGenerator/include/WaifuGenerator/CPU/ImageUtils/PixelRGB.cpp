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
