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

