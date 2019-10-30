#include "fieldVariable.h"

FieldVariable::FieldVariable(std::array<int,2> size, std::array<double,2> origin, std::array<double,2> meshWidth) : 
    Array2D(size), origin_(origin), meshWidth_(meshWidth)
{
    
}

void FieldVariable::print()
{
    std::cout.precision(2);
    std::cout << std::scientific;
    for (int j = this->size()[1] - 1; j >= 0 ; --j) {
        for (int i = 0; i <= this->size()[0] - 1; ++i) {
            // marke boundary different than inner values
            if ((i == 0) | (j == 0) | (i == this->size()[0] - 1) || (j == this->size()[1] - 1)) {
                // blue background, magenta foreground
                std::cout << "\033[42;35m";
            } else {
                // blue background, magenta foreground
                std::cout << "\033[43;34m";
            }

            // add 0 if neccessary
            if ((*this)(i, j) >= 0.0) {
                std::cout << '+' << (*this)(i, j) << std::scientific << " ";
            } else {
                std::cout << (*this)(i, j) << std::scientific << " ";
            }
            // default background, default foreground
            std::cout << "\033[49;39m";
        }
        std::cout << std::endl;
    }
    std::cout.unsetf(std::ios_base::floatfield);
}
