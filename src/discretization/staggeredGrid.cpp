#include "staggeredGrid.h"

StaggeredGrid::StaggeredGrid(std::array<int,2> size, std::array<double,2> meshWidth) :
    u({ size[0] - 1, size[1] }, { 0.0, -0.5 * meshWidth[1] }, meshWidth),
    v({ size[0], size[1] - 1 }, { -0.5 * meshWidth[0], 0.0 }, meshWidth),
    p({ size[0], size[1] }, { -0.5 * meshWidth[0], -0.5 * meshWidth[1] }, meshWidth),
    f({ size[0] - 1, size[1] }, { 0.0, -0.5 * meshWidth[1] }, meshWidth),
    g({ size[0], size[1] - 1 }, { -0.5 * meshWidth[0], 0.0 }, meshWidth),
    rhs({ size[0], size[1] }, { -0.5 * meshWidth[0], -0.5 * meshWidth[1] }, meshWidth),
    meshWidth_(meshWidth)
{
    
}

StaggeredGrid::~StaggeredGrid()
{
    // TODO: check if member variables has to be deleted manually
}

double StaggeredGrid::dx() const
{
    return meshWidth_[0];
}

double StaggeredGrid::dy() const
{
    return meshWidth_[1];
}

int StaggeredGrid::uIBegin() const
{
    return -1;
}

int StaggeredGrid::uJBegin() const
{
    return -1;
}

int StaggeredGrid::uIEnd() const
{
    return u.sizeX() - 1;
}

int StaggeredGrid::uJEnd() const
{
    return u.sizeY() - 1;
}

int StaggeredGrid::vIBegin() const
{
    return -1;
}

int StaggeredGrid::vJBegin() const
{
    return -1;
}

int StaggeredGrid::vIEnd() const
{
    return v.sizeX() - 1;
}

int StaggeredGrid::vJEnd() const
{
    return v.sizeY() - 1;
}

int StaggeredGrid::pIBegin() const
{
    return -1;
}

int StaggeredGrid::pJBegin() const
{
    return -1;
}

int StaggeredGrid::pIEnd() const
{
    return p.sizeX() - 1;
}

int StaggeredGrid::pJEnd() const
{
    return p.sizeY() - 1;
}
