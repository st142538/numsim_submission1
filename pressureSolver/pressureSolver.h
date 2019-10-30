#pragma once

#include "../discretization/discretization.h"
#include <memory>

/** This class represents the abstract class for pressure solvers.
 */
class PressureSolver
{
protected:
    std::shared_ptr<Discretization> discretization_;

public:

    PressureSolver(std::shared_ptr<Discretization> discretization);

    //! iterate one step of pressure solver and returns squared residual
    virtual double iterate() const = 0;
};
