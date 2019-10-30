#include "computation.h"

int main(int argc, char *argv[]) 
{
    Computation computation("parameters.txt");

    computation.testDiscretization();
    computation.testSettings();
    computation.testTimestep();

    computation.runSimulation();
}