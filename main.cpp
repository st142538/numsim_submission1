#include "computation.h"

int main(int argc, char *argv[]) 
{
    Computation computation("parameters.txt");
    computation.testSettings();
    computation.runSimulation();
}