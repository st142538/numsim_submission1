#include "fieldVariable.h"

FieldVariable::FieldVariable(std::array<int,2> size, std::array<double,2> origin, std::array<double,2> meshWidth) : 
    Array2D(size), origin_(origin), meshWidth_(meshWidth)
{
    
}

double FieldVariable::interpolateAt(double x, double y)
{
    // calculate corspeonding cell (bottom left point)
    // cartesian (0,0) -> index (0,0) etc.
    int i = std::floor((x - origin_[0])/ meshWidth_[0] );
    int j = std::floor((y - origin_[1])/ meshWidth_[1] );

    // calculate cartesian coordinates of the bottom left point
    double blX = i * meshWidth_[0] + origin_[0];
    double blY = j * meshWidth_[1] + origin_[1];

    // calculate distances for bilinear interpolation
    // distance to bottom left point
    double blDistanceX = x - blX;
    double blDistanceY = y - blY;

    // calculate coefficient for bilinear interpolation
    double alphaX = blDistanceX / meshWidth_[0];
    double alphaY = blDistanceY / meshWidth_[1];

    // calculate bilinear interpolation for cartesian (x,y)
    return (1 - alphaX) * (1- alphaY) * (*this)(i, j)
        + alphaX * (1- alphaY) * (*this)(i + 1, j)
        + (1 - alphaX) * alphaY * (*this)(i, j + 1)
        + alphaX * alphaY * (*this)(i + 1, j + 1);
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
