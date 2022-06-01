#include "waifupch.h"

#include <WaifuGenerator/CPU/NetworkAttributes/Network.h>
#include <WaifuGenerator/CPU/DataIO/NNTrainer.h>

int main(int argc, char** argv)
{
    srand(time(NULL));

    _WF_CALL NNTrainer networkTrainer("AnimeFaceTrainingData.txt");

    std::vector<_WF_CALL PixelRGB> inputValues;
    std::vector<_WF_CALL PixelRGB> targetValues;
    std::vector<_WF_CALL PixelRGB> resultValues;

    _WF_CALL Network NeuralNetwork(64*64, 2, (64*64) + 1);
    std::cout << "NEURAL NETWORK INITIALIZED SUCCESSFULLY\n";

    size_t trainingPass = 0;
    size_t count = 0;
    while (trainingPass != 492) 
    {
        trainingPass += 1;
        count += 1;
        std::cout << "\nTRAINING PASS #" << trainingPass << "\n";

        networkTrainer.getNextModel(inputValues);
        targetValues = inputValues;
        NeuralNetwork.feedForward(inputValues);
        std::cout << "FEEDFORWARD #" << trainingPass << " DONE SUCCESSFULLY\n";

        resultValues = NeuralNetwork.getResult();
        if (count == 100) {
            networkTrainer.writeOutputToFile(resultValues, "Out/NNOutput.txt");
            count = 1;
        }
        std::cout << "RESULT #" << trainingPass << " SUCCESSFULLY SAVED\n";

        NeuralNetwork.backPropagate(targetValues);
        std::cout << "BACKPROPAGATE #" << trainingPass << " DONE SUCCESSFULLY\n\n";

        std::cout << "AVERAGE RED ERROR: " << NeuralNetwork.getAverageRedChannelError() << "\n";
        std::cout << "AVERAGE GREEN ERROR: " << NeuralNetwork.getAverageGreenChannelError() << "\n";
        std::cout << "AVERAGE BLUE ERROR: " << NeuralNetwork.getAverageBlueChannelError() << "\n";
    }

    networkTrainer.writeOutputToFile(resultValues, "Out/NNOutput.txt");

    return 0;
}