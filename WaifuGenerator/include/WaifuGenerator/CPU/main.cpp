#include "waifupch.h"

#include <WaifuGenerator/CPU/NetworkAttributes/Network.h>
#include <WaifuGenerator/CPU/TrainingData/NNTrainer.h>

int main(int argc, char** argv)
{
    srand(time(NULL));

    _WF_CALL NNTrainer networkTrainer("AnimeFaceTrainingData.txt");

    std::vector<_WF_CALL PixelRGB> inputValues;
    std::vector<_WF_CALL PixelRGB> targetValues;
    std::vector<_WF_CALL PixelRGB> resultValues;

    _WF_CALL Network NeuralNetwork(64*64, 2, (64*64) + 1);
    std::cout << "NEURAL NETWORK INITIALIZED SUCCESSFULLY\n";

    networkTrainer.getNextModel(inputValues);
    targetValues = inputValues;

    size_t trainingPass = 0;
    while (trainingPass != 15) 
    {
        trainingPass += 1;
        std::cout << "TRAINING PASS #" << trainingPass << "\n";

        networkTrainer.getNextModel(inputValues);
        //targetValues = inputValues;
        NeuralNetwork.feedForward(inputValues);
        std::cout << "FEEDFORWARD #" << trainingPass << " DONE SUCCESSFULLY\n";

        resultValues = NeuralNetwork.getResult();
        networkTrainer.writeOutputToFile(resultValues, 64, 64);
        std::cout << "RESULT #" << trainingPass << " SUCCESSFULLY SAVED\n";

        NeuralNetwork.backPropagate(targetValues);
        std::cout << "BACKPROPAGATE #" << trainingPass << " DONE SUCCESSFULLY\n\n";

        std::cout << "AVERAGE RED ERROR: " << NeuralNetwork.getAverageRedChannelError() << "\n";
        std::cout << "AVERAGE GREEN ERROR: " << NeuralNetwork.getAverageGreenChannelError() << "\n";
        std::cout << "AVERAGE BLUE ERROR: " << NeuralNetwork.getAverageBlueChannelError() << "\n";
    }

    return 0;
}