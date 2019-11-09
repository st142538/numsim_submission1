#include "gaussSeidel.h"

GaussSeidel::GaussSeidel(std::shared_ptr<Discretization> discretization) :
    PressureSolver(discretization)
{

}

void GaussSeidel::iterate() const
{
    double factor = 0.5
    * (std::pow(discretization_->dx(), 2) * std::pow(discretization_->dy(), 2)) 
    / (std::pow(discretization_->dx(), 2) + std::pow(discretization_->dy(), 2));

    double residual = 0.0;

    // solve step
    for (int j = 1; j < discretization_->p.sizeY() - 1; ++j)
    {
        for (int i = 1; i < discretization_->p.sizeX() - 1; ++i)
        {
            discretization_->p(i,j) = factor 
                * ((discretization_->p(i-1,j) + discretization_->p(i+1,j)) 
                    / std::pow(discretization_->dx(), 2)
                    + (discretization_->p(i,j-1) + discretization_->p(i,j+1)) 
                    / std::pow(discretization_->dy(), 2) 
                    - discretization_->rhs(i,j));
        }
    }
}
