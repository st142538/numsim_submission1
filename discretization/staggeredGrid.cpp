#include "staggeredGrid.h"

StaggeredGrid::StaggeredGrid(std::array<int,2> size, std::array<double,2> meshWidth) :
    u({ size[0] - 1, size[1] }, { 0, -0.5 * meshWidth[1] }, meshWidth),
    v({ size[0], size[1] - 1 }, { -0.5 * meshWidth[0], 0 }, meshWidth),
    p({ size[0], size[1] }, { -0.5 * meshWidth[0], -0.5 * meshWidth[1] }, meshWidth),
    f({ size[0] - 1, size[1] }, { 0, -0.5 * meshWidth[1] }, meshWidth),
    g({ size[0], size[1] - 1 }, { -0.5 * meshWidth[0], 0 }, meshWidth),
    rhs({ size[0], size[1] }, { -0.5 * meshWidth[0], -0.5 * meshWidth[1] }, meshWidth),
    meshWidth_(meshWidth)
{

}

void StaggeredGrid::setPBoundaries()
{
    // set the 4 corner boundary cells
    p(0, 0) = p(1, 1);                                                  // bottom left
    p(p.sizeX() - 1, 0) = p(p.sizeX() - 2, 1);                          // bottom right
    p(0, p.sizeY() - 1) = p(1, p.sizeY() - 2);                          // top left
    p(p.sizeX() - 1, p.sizeY() - 1) = p(p.sizeX() - 2, p.sizeY() - 2);  // top right

    // set the top and bottom boundaries edges except corner cells
    for (int i = 1; i < p.sizeX() - 1; ++i)
    {
        p(i, 0) = p(i, 1);                          // bottom
        p(i, p.sizeY() - 1) = p(i, p.sizeY() - 2);  // top
    }

    // set the left and right boundaries edges except corner cells
    for (int j = 1; j < p.sizeY() - 1; ++j)
    {
        p(0, j) = p(1, j);                          // left
        p(p.sizeX() - 1, j) = p(p.sizeX() - 2, j);  // right
    }
}

void StaggeredGrid::setUVBoundaries(
    std::array<double,2> bottom,
    std::array<double,2> top,
    std::array<double,2> left,
    std::array<double,2> right)
{
    // set the left and right boundary edge for u (velocity in x direction)
    // except the corner cells
    for (int j = 1; j < u.sizeY() - 1; ++j)
    {
        u(0, j) = left[0];
        u(u.sizeX() - 1, j) = right[0];
    }
    // set the bottom and top boundary edge for u (velocity in x direction)
    // with the corner cells
    for (int i = 0; i < u.sizeX(); ++i)
    {
        u(i, 0) = 2 * bottom[0] - u(i, 1);
        u(i, u.sizeY() - 1) = 2 * top[0] - u(i, u.sizeY() - 2);
    }

    // set the bottom and top boundary edge for v (velocity in y direction)
    // except the corner cells
    for (int i = 1; i < v.sizeX() - 1; ++i)
    {
        v(i, 0) = bottom[1];
        v(i, v.sizeY() - 1) = top[1];
    }

    // set the left and right boundary edge for v (velocity in y direction)
    // with the corner cells
    for (int j = 0; j < v.sizeY(); ++j)
    {
        v(0, j) = 2 * left[1] - v(1, j);
        v(v.sizeX() - 1, j) = 2 * right[1] - v(v.sizeX() - 2, j);
    }
}
