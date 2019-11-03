#pragma once

#include "pressureSolver.h"
#include "../discretization/discretization.h"
#include <memory>

/** This class represents the SOR solver.
 */
class SOR :
    public PressureSolver
{
private:
    double omegaSOR_;

public:

    SOR(std::shared_ptr<Discretization> discretization, double omegaSOR);

    //! iterate one step of SOR solver and returns squared residual
    double iterate() const;
};
