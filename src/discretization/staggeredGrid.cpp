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