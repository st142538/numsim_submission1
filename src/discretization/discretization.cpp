#include "discretization.h"

Discretization::Discretization(std::array<int,2> nCells, std::array<double,2> meshWidth) :
    StaggeredGrid(nCells, meshWidth)
{
    
}

double Discretization::computeD2uDx2(int i, int j) const
{
    return (u(i-1,j) - 2 * u(i,j) + u(i+1,j)) / std::pow(dx(), 2);
}

double Discretization::computeD2vDy2(int i, int j) const
{
    return (v(i,j-1) - 2 * v(i,j) + v(i,j+1)) / std::pow(dy(), 2);
}

double Discretization::computeD2uDy2(int i, int j) const
{
    return (u(i,j-1) - 2 * u(i,j) + u(i,j+1)) / std::pow(dy(), 2);
}

double Discretization::computeD2vDx2(int i, int j) const
{
    return (v(i-1,j) - 2 * v(i,j) + v(i+1,j)) / std::pow(dx(), 2);
}

double Discretization::computeDpDx(int i, int j) const
{
    // single diffquotient, the point is calculated
    // for the center between two pressure points
    // and lays on the u point
    return (p(i+1,j) - p(i,j)) / dx();
}

double Discretization::computeDpDy(int i, int j) const
{
    // single diffquotient, the point is calculated
    // for the center between two pressure points
    // and lays on the v point
    return (p(i,j+1) - p(i,j)) / dy();
}
