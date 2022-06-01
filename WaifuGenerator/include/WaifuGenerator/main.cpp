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
    while (trainingPass != 15)
    {
        trainingPass += 1;
        count += 1;
        std::cout << "\nTRAINING PASS #" << trainingPass << "\n";

        networkTrainer.getNextModel(inputValues);
        targetValues = inputValues;
        NeuralNetwork.feedForward(inputValues);
        std::cout << "FEEDFORWARD #" << trainingPass << " DONE SUCCESSFULLY\n";

        resultValues = NeuralNetwork.getResult();
        /*if (count == 100) {
            networkTrainer.writeOutputToFile(resultValues, "Out/NNOutput.txt");
            count = 1;
        }*/
        std::cout << "RESULT #" << trainingPass << " SUCCESSFULLY SAVED\n";

        NeuralNetwork.backPropagate(targetValues);
        std::cout << "BACKPROPAGATE #" << trainingPass << " DONE SUCCESSFULLY\n\n";

        std::cout << "AVERAGE RED ERROR: " << NeuralNetwork.getAverageRedChannelError() << "\n";
        std::cout << "AVERAGE GREEN ERROR: " << NeuralNetwork.getAverageGreenChannelError() << "\n";
        std::cout << "AVERAGE BLUE ERROR: " << NeuralNetwork.getAverageBlueChannelError() << "\n";
    }

    NeuralNetwork.saveConfiguration();
    networkTrainer.writeOutputToFile(resultValues, "Out/NNOutput.txt");

    return 0;
}