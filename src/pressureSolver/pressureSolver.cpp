#include "pressureSolver.h"

PressureSolver::PressureSolver(std::shared_ptr<Discretization> discretization) :
    discretization_(discretization)
{
    
}

double PressureSolver::squaredResidual() const
{
    double residual = 0.0;

    // calculate squared residual 
    for (int j = 1; j < discretization_->p.sizeY() - 1; ++j)
    {
        for (int i = 1; i < discretization_->p.sizeX() - 1; ++i)
        {
            residual = residual + std::pow(
                discretization_->rhs(i,j) 
                    - (discretization_->p(i-1,j) - 2 * discretization_->p(i,j) + discretization_->p(i+1,j)) 
                        / std::pow(discretization_->dx(),2) 
                    - (discretization_->p(i,j-1) - 2 * discretization_->p(i,j) + discretization_->p(i,j+1)) 
                        / std::pow(discretization_->dy(),2)
                ,2);
        }
    }
    
    return residual;
}