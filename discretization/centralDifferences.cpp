#include "centralDifferences.h"

CentralDifferences::CentralDifferences(std::array<int,2> nCells, std::array<double,2> meshWidth) :
    Discretization(nCells, meshWidth)
{
    
}

double CentralDifferences::computeDu2Dx(int i, int j) const
{
    double avgURight = std::pow((u(i+1,j) + u(i,j)) / 2.0,2);
    double avgULeft = std::pow((u(i,j) + u(i-1,j)) / 2.0,2);
    return (avgURight - avgULeft) / meshWidth_[0];
}

double CentralDifferences::computeDv2Dy(int i, int j) const
{
    double avgVTop = std::pow((v(i,j+1) + v(i,j)) / 2.0,2);
    double avgVBottom = std::pow((v(i,j) + v(i,j-1)) / 2.0,2);
    return (avgVTop - avgVBottom) / meshWidth_[1];
}

double CentralDifferences::computeDuvDx(int i, int j) const
{
    double avgUTop = (u(i,j+1) + u(i,j)) / 2.0;
    double avgUTop2 = (u(i-1,j+1) + u(i-1,j)) / 2.0;
    double avgVRight = (v(i+1,j) + v(i,j)) / 2.0;
    double avgVLeft = (v(i-1,j) + v(i,j)) / 2.0;
    return (avgUTop * avgVRight - avgUTop2 * avgVLeft) / meshWidth_[0];
}

double CentralDifferences::computeDuvDy(int i, int j) const
{
    double avgVRight = (v(i+1,j) + v(i,j)) / 2.0;
    double avgVRight2 = (v(i+1,j-1) + v(i,j-1)) / 2.0;
    double avgUTop = (u(i,j+1) + u(i,j)) / 2.0;
    double avgUBottom = (u(i,j) + u(i,j-1)) / 2.0;
    return (avgVRight * avgUTop - avgVRight2 * avgUBottom) / meshWidth_[1];
}
