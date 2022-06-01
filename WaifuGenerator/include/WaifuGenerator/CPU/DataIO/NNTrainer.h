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
#ifndef CPU_WAIFUGENERATOR_NNTRAINER_H
#define CPU_WAIFUGENERATOR_NNTRAINER_H

#include <WaifuGenerator/CPU/ImageUtils/PixelRGB.h>
#include <WaifuGenerator/CPU/NetworkAttributes/Core.h>

_WF_BEGIN

    class NNTrainer
    {
    private:
        std::ifstream m_DataStream;
        std::ofstream m_OutputStream;

    public:
        NNTrainer(const std::string filename);
        ~NNTrainer();

        bool isEOF();
        void getNextModel(std::vector<PixelRGB>& inputValues);
        void writeOutputToFile(std::vector<PixelRGB>& outputValues, std::string path);

    };

_WF_END

#endif // !CPU_WAIFUGENERATOR_NNTRAINER_H


