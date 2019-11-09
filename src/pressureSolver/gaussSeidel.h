#pragma once

#include "pressureSolver.h"
#include "../discretization/discretization.h"
#include <memory>

/** This class represents the gauss seidel solvers.
 */
class GaussSeidel :
    public PressureSolver
{
public:

    GaussSeidel(std::shared_ptr<Discretization> discretization);

    //! iterate one step of gauss seidel solver
    void iterate() const;
};
