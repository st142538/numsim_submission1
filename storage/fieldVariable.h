#pragma once

#include "array2d.h"
#include <vector>
#include <array>
#include <iostream>

/** This class represents a field variable of double values.
 *  Internally they use the array2d as memory type.
 *  A field varaible contains all inner cells and helo cells!
 *  Note, that the size is now nCellsX + 2 resp. nCellsY + 2.
 *  The entries can be accessed by two indices i,j.
 */
class FieldVariable : 
    public Array2D
{
    private:

    const std::array<double,2> origin_;
    const std::array<double,2> meshWidth_;

public:
    //! constructor
    FieldVariable(std::array<int,2> size, std::array<double,2> origin, std::array<double,2> meshWidth);

    //! prints the content of the field variable
    void print();
};
