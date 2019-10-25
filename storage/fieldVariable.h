#pragma once

#include "array2d.h"
#include <vector>
#include <array>

/** This class represents a field variable of double values.
 *  Internally they use the array2d as memory type.
 *  A field varaible contains all inner cells and helo cells!
 *  Note, that the size is now nCellsX + 2 resp. nCellsY + 2.
 *  The entries can be accessed by two indices i,j.
 */
class FieldVariable : 
    public Array2D
{
public:

    //! constructor
    FieldVariable(std::array<int,2> size);
};
