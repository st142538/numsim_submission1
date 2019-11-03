#include "donorCell.h"

DonorCell::DonorCell(std::array<int,2> nCells, std::array<double,2> meshWidth, double alphaDC) :
    Discretization(nCells, meshWidth), alphaDC_(alphaDC)
{
    
}

double DonorCell::computeDu2Dx(int i, int j) const
{
    double avgURightPlus = (u(i+1,j) + u(i,j)) / 2.0;
    double avgULeftPlus = (u(i,j) + u(i-1,j)) / 2.0;
    double avgURightMinus = (u(i,j) - u(i+1,j)) / 2.0;
    double avgULeftMinus = (u(i-1,j) - u(i,j)) / 2.0;

    double firstSum = std::pow(avgURightPlus,2) - std::pow(avgULeftPlus,2);
    double secondSum = std::abs(avgURightPlus) * avgURightMinus - std::abs(avgULeftPlus) * avgULeftMinus;
    
    return (firstSum + alphaDC_ * secondSum) / meshWidth_[0];
}

double DonorCell::computeDv2Dy(int i, int j) const
{
    double avgVTopPlus = (v(i,j+1) + v(i,j)) / 2.0;
    double avgVBottomPlus = (v(i,j) + v(i,j-1)) / 2.0;
    double avgVTopMinus = (v(i,j+1) - v(i,j)) / 2.0;
    double avgVBottomMinus = (v(i,j) - v(i,j-1)) / 2.0;

    double firstSum = std::pow(avgVTopPlus,2) - std::pow(avgVBottomPlus,2);
    double secondSum = std::abs(avgVTopPlus) * avgVTopMinus - std::abs(avgVBottomPlus) * avgVBottomMinus;
    
    return (firstSum + alphaDC_ * secondSum) / meshWidth_[1];
}

double DonorCell::computeDuvDx(int i, int j) const
{
    double avgUTop = (u(i,j+1) + u(i,j)) / 2.0;
    double avgUTop2 = (u(i-1,j+1) + u(i-1,j)) / 2.0;
    double avgVRightPlus = (v(i,j) + v(i+1,j)) / 2.0; 
    double avgVRightMinus = (v(i,j) - v(i+1,j)) / 2.0; 
    double avgVLeftPlus = (v(i-1,j) + v(i,j)) / 2.0; 
    double avgVLeftMinus = (v(i-1,j) - v(i,j)) / 2.0; 

    double firstSum = avgUTop * avgVRightPlus - avgUTop2 * avgVLeftPlus;
    double secondSum = std::abs(avgUTop) * avgVRightMinus - std::abs(avgUTop2) * avgVLeftMinus;

    return (firstSum + alphaDC_ * secondSum) / meshWidth_[0];
}

double DonorCell::computeDuvDy(int i, int j) const
{
    double avgVRight = (v(i+1,j) + v(i,j)) / 2.0;
    double avgVRight2 = (v(i+1,j-1) + v(i,j-1)) / 2.0;
    double avgUTopPlus = (u(i,j) + u(i,j+1)) / 2.0; 
    double avgUTopMinus = (u(i,j) - u(i,j+1)) / 2.0;
    double avgUBottomPlus = (u(i,j-1) + u(i,j)) / 2.0; 
    double avgUBottomMinus = (u(i,j-1) - u(i,j)) / 2.0;  

    double firstSum = avgVRight * avgUTopPlus - avgVRight2 * avgUBottomPlus;
    double secondSum = std::abs(avgVRight) * avgUTopMinus - std::abs(avgVRight2) * avgUBottomMinus;

    return (firstSum + alphaDC_ * secondSum) / meshWidth_[1];
}
