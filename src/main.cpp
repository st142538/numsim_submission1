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

    // print pretty header :)
    std::cout << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "| Fluid solver for NumSim Exercise 1 |" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << std::endl;

    Computation computation(parametersFilePath);
    computation.printSettings();

    std::cout << std::endl;
    std::cout << "starting simulation..." << std::endl;
    std::cout << std::endl;

    computation.runSimulation();

    std::cout << std::endl;
    std::cout << "finished simulation successfully!" << std::endl;
    std::cout << std::endl;
}