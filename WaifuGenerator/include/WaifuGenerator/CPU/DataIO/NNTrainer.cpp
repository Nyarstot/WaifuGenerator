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
#include "NNTrainer.h"

WaifuCPU::NNTrainer::NNTrainer(const std::string filename)
{
    m_DataStream.open(filename.c_str());
}

WaifuCPU::NNTrainer::~NNTrainer()
{
    m_DataStream.close();
}

bool _WF_CALL NNTrainer::isEOF()
{
    return m_DataStream.eof();
}

void _WF_CALL NNTrainer::getNextModel(std::vector<PixelRGB>& inputValues)
{
    const std::regex m_PixelDataParse("[0-9.]+");
    std::string line;

    inputValues.clear();

    while (!this->isEOF())
    {
        std::getline(m_DataStream, line);
        if (line == "<TRAIN_DATA_REGION_END>") {
            break;
        }

        const std::vector<std::smatch> match{
            std::sregex_iterator {C_ALL(line), m_PixelDataParse},
            std::sregex_iterator {}
        };

        for (size_t i = 2; i < match.size(); i += 3) {
            PixelRGB tmp(
                std::stod(match[i - 2].str()),
                std::stod(match[i - 1].str()),
                std::stod(match[i].str())
            );

            inputValues.push_back(tmp);
        }
    }
}

void _WF_CALL NNTrainer::writeOutputToFile(std::vector<PixelRGB>& outputValues, std::string path)
{
    m_OutputStream.open(path, std::ios_base::app);

    for (size_t i{}; i < outputValues.size(); i++) {
        m_OutputStream << outputValues[i];
    }
    m_OutputStream << "\n<END>\n";

    m_OutputStream.close();
}

