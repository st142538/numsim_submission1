#include "staggeredGrid.h"

StaggeredGrid::StaggeredGrid(std::array<int,2> size) :
    u(size), v(size), p(size), f(size), g(size), rhs(size)
{

}

void StaggeredGrid::setPBoundaries()
{
    // set the 4 corner boundary cells
    p(0, 0) = p(1, 1);                                          // bottom left
    p(p.sizeX(), 0) = p(p.sizeX(), 1);                          // bottom right
    p(0, p.sizeY()) = p(1, p.sizeY() - 1);                      // top left
    p(p.sizeX(), p.sizeY()) = p(p.sizeX() - 1, p.sizeY() - 1);  // top right

    // set the top and bottom boundaries edges
    for (int i = 1; i < p.sizeX() - 1; ++i)
    {
        p(i, 0) = p(i, 1);                  // bottom
        p(i, p.sizeY()) = p(i, p.sizeY() - 1);  // top
    }

    // set the left and right boundaries edges
    for (int j = 1; j < p.sizeY() - 1; ++j)
    {
        p(0, j) = p(1, j);                  // left
        p(p.sizeX(), j) = p(p.sizeX() - 1, j);  // right
    }
}

void StaggeredGrid::setUVBoundaries(
    std::array<double,2> bottom,
    std::array<double,2> top,
    std::array<double,2> left,
    std::array<double,2> right)
{
    // set boundary conditions for u (velocity in x direction)
    // set the 4 corner boundary cells
    u(0, 0) = 0.0;                  // bottom left
    u(u.sizeX(), 0) = 0.0;          // bottom right
    u(0, u.sizeY()) = 0.0;          // top left
    u(u.sizeX(), u.sizeY()) = 0.0;  // top right

    // set the left boundary edge for u (velocity in x direction)
    for (int j = 1; j < u.sizeY() - 1; ++j)
    {
        u(0, j) = left[0];
    }
    // set the bottom boundary edge for u (velocity in x direction)
    for (int i = 1; i < u.sizeX() - 1; ++i)
    {
        u(i, 0) = 2 * bottom[0] - u(i, 1);
    }
    // set the top boundary edge for u (velocity in x direction)
    for (int i = 1; i < u.sizeX() - 1; ++i)
    {
        u(i, u.sizeY()) = 2 * top[0] - u(i, u.sizeY() - 1);
    }

    // set boundary conditions for v (velocity in y direction)
    // set the 4 corner boundary cells
    v(0, 0) = 0.0;                  // bottom left
    v(v.sizeX(), 0) = 0.0;          // bottom right
    v(0, v.sizeY()) = 0.0;          // top left
    v(v.sizeX(), v.sizeY()) = 0.0;  // top right

    // set the left boundary edge for v (velocity in y direction)
    for (int j = 1; j < v.sizeY() - 1; ++j)
    {
        v(0, j) = 2 * left[1] - v(1, j);
    }
    // set the bottom boundary edge for v (velocity in y direction)
    for (int i = 1; i < v.sizeX() - 1; ++i)
    {
        v(i, 0) = bottom[1];
    }
    // set the right boundary edge for u (velocity in x direction)
    for (int j = 1; j < v.sizeY() - 1; ++j)
    {
        v(v.sizeX(), j) = 2 * right[1] - v(v.sizeX() - 1, j);
    }
}
