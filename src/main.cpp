#include "computation.h"

int main(int argc, char *argv[]) 
{
    if (argc <= 1)
    {
        std::cout << "Please specify a parameters file." << std::endl;
        return 0;
    }

    // parse path for parameters file
    std::string parametersFilePath = argv[1];

    Computation computation(parametersFilePath);
    computation.printSettings();
    computation.runSimulation();
}