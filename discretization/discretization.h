#pragma once

#include "staggeredGrid.h"
#include <cmath>

class Discretization :
    public StaggeredGrid
{
public:

    //! construct the object with given number of cells in x and y direction
    Discretization(std::array<int,2> nCells, std::array<double,2> meshWidth);

    //! compute the 1st derivative ∂ u^2 / ∂x
    virtual double computeDu2Dx(int i, int j) const = 0;

    //! compute the 1st derivative ∂ v^2 / ∂x
    virtual double computeDv2Dy(int i, int j) const = 0;

    //! compute the 1st derivative ∂ (uv) / ∂x
    virtual double computeDuvDx(int i, int j) const = 0;

    //! compute the 1st derivative ∂ (uv) / ∂y
    virtual double computeDuvDy(int i, int j) const = 0;

    //! compute the 2nd derivative ∂² u / ∂x²
    virtual double computeD2uDx2(int i, int j) const;

    //! compute the 2nd derivative ∂² v / ∂y²
    virtual double computeD2vDy2(int i, int j) const;

    //! compute the 2nd derivative ∂² u / ∂y²
    virtual double computeD2uDy2(int i, int j) const;

    //! compute the 2nd derivative ∂² v / ∂x²
    virtual double computeD2vDx2(int i, int j) const;

    //! compute the 1st derivative ∂ p / ∂x
    virtual double computeDpDx(int i, int j) const;

    //! compute the 1st derivative ∂ p / ∂y
    virtual double computeDpDy(int i, int j) const;
};
