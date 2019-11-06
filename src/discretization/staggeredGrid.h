#pragma once

#include "../storage/fieldVariable.h"
#include <vector>
#include <array>

/** This class represents the staggered grid, 
 *  i.e. the field variables u, v, p, f, g, rhs.
 */
class StaggeredGrid
{
private:
    std::array<double,2> meshWidth_;

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

    double dx() const;
    double dy() const;
    int uIBegin() const;
    int uJBegin() const;
    int uIEnd() const;
    int uJEnd() const;
    int vIBegin() const;
    int vJBegin() const;
    int vIEnd() const;
    int vJEnd() const;
    int pIBegin() const;
    int pJBegin() const;
    int pIEnd() const;
    int pJEnd() const;
};
