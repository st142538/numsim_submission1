#include "storage/staggeredGrid.h"
#include "settings.h"

template<typename T>
void PrintVectorAsMatrix(T *vec, const unsigned int n)
{
    std::cout.precision(2);
    std::cout << std::scientific;
    for (unsigned int i = n + 2; i >= 1 ; --i) {
        for (unsigned int j = 0; j < n + 2; ++j) {
            unsigned int index = (i - 1) * (n + 2) + j;
            // marke boundary different than inner values
            if (i == 1 | j == 0 | i == n + 2 || j == n + 1) {
                // blue background, magenta foreground
                std::cout << "\033[42;35m";
            } else {
                // blue background, magenta foreground
                std::cout << "\033[43;34m";
            }

            // add 0 if neccessary
            if (((double) vec[index]) >= 0.0) {
                std::cout << '+' << (double) vec[index] << std::scientific << " ";
            } else {
                std::cout << (double) vec[index] << std::scientific << " ";
            }
            // default background, default foreground
            std::cout << "\033[49;39m";
        }
        std::cout << std::endl;
    }
    std::cout.unsetf(std::ios_base::floatfield);
}

void testSettings()
{
    Settings settings;
    settings.loadFromFile("parameters.txt");
    settings.printSettings();
}

void testStaggeredGrid()
{
    Settings settings;
    settings.loadFromFile("parameters.txt");

    // here should nCells -> nCells + 2 for x and y direction
    StaggeredGrid grid(settings.nCells);
    grid.setPBoundaries();
}

int main(int argc, char *argv[]) 
{
    testStaggeredGrid();
}