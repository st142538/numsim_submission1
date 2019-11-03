#pragma once

#include "../storage/fieldVariable.h"
#include <vector>
#include <array>

/** This class represents the staggered grid, 
 *  i.e. the field variables u, v, p, f, g, rhs.
 */
class StaggeredGrid
{
public:
    FieldVariable u;    //< field varaible for velocity in x direction
    FieldVariable v;    //< field varaible for velocity in y direction
    FieldVariable p;    //< field varaible for pressure
    FieldVariable f;    //< field varaible for temp velocity in x direction
    FieldVariable g;    //< field varaible for temp velocity in x direction
    FieldVariable rhs;  //< field varaible for the rhs

    //! constructor
    StaggeredGrid(std::array<int,2> size, std::array<double,2> meshWidth);

    //! destructor
    ~StaggeredGrid();

    std::array<double,2> meshWidth_;
};
