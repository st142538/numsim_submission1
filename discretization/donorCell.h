#pragma once

#include "discretization.h"
#include <cmath>

class DonorCell :
    public Discretization
{
private:

    double alphaDC_;

public:

    DonorCell(std::array<int,2> nCells, std::array<double,2> meshWidth, double alphaDC);

    //! compute the 1st derivative ∂ u^2 / ∂x
    virtual double computeDu2Dx(int i, int j) const;

    //! compute the 1st derivative ∂ v^2 / ∂x
    virtual double computeDv2Dy(int i, int j) const;

    //! compute the 1st derivative ∂ (uv) / ∂x
    virtual double computeDuvDx(int i, int j) const;

    //! compute the 1st derivative ∂ (uv) / ∂y
    virtual double computeDuvDy(int i, int j) const;
};