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
#ifndef CPU_WAIFUGENERATOR_PIXELRGB_H
#define CPU_WAIFUGENERATOR_PIXELRGB_H

#include <WaifuGenerator/CPU/NetworkAttributes/Core.h>

_WF_BEGIN

    class PixelRGB
    {
    private:
        //double* m_RGBChannels;
        std::vector<double> m_RGBChannels;

    public:
        PixelRGB();
        PixelRGB(const double& R, const double& G, const double& B);
        PixelRGB(const PixelRGB& buffer);

        const double& operator[] (size_t index) const
        {
            if (index >= 3) {
                throw std::overflow_error("Index is out of range");
            }

            return m_RGBChannels[index];
        }

        double& operator[] (size_t index)
        {
            if (index >= 3) {
                throw std::overflow_error("Index is out of range");
            }

            return m_RGBChannels[index];
        }

        friend std::ostream& operator<<(std::ostream& os, const PixelRGB& pd) 
        {
            os << "[ " << pd.m_RGBChannels[0] << ", " << pd.m_RGBChannels[1] << ", " << pd.m_RGBChannels[2] << " ]";
            return os;
        }

    };

_WF_END

#endif // !CPU_WAIFUGENERATOR_PIXELRGB_H


