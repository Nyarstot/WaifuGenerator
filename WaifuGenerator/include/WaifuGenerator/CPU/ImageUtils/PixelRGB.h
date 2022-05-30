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


