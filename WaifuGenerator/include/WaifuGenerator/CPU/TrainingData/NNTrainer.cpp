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

void _WF_CALL NNTrainer::writeOutputToFile(std::vector<PixelRGB>& outputValues, size_t height, size_t width)
{
    /*size_t c = 0;

    for (size_t i{}; i < height; i++) {
        for (size_t j{}; j < width; j++) {
            m_OutputStream << outputValues[c];
            c += 1;
        }
        m_OutputStream << "\n";
    }
    m_OutputStream << "<END>\n";*/

    m_OutputStream.open("NNOutput.txt", std::ios_base::app);

    for (size_t i{}; i < outputValues.size(); i++) {
        m_OutputStream << outputValues[i];
    }
    m_OutputStream << "\n<END>\n";

    m_OutputStream.close();
}

void _WF_CALL NNTrainer::test()
{
    const std::regex m_PixelDataParse("[0-9.]+");
    std::string line;

    m_Prekol.clear();

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

        for (size_t i = 2; i < match.size(); i+=3) {
            PixelRGB tmp(
                std::stod(match[i - 2].str()),
                std::stod(match[i - 1].str()),
                std::stod(match[i].str())
            );

            m_Prekol.push_back(tmp);
        }
    }
}

