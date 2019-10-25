#pragma once

#include "fieldVariable.h"
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
    StaggeredGrid(std::array<int,2> size);

    //! sets/updates the boundaries for the pressure field p
    void setPBoundaries();

    //! sets/updates the boundaries for the velocity fields u and v
    void setUVBoundaries(
        std::array<double,2> bottom,
        std::array<double,2> top,
        std::array<double,2> left,
        std::array<double,2> right);
};
