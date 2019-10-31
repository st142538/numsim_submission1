#include "sor.h"

SOR::SOR(std::shared_ptr<Discretization> discretization, double omegaSOR) :
    PressureSolver(discretization), omegaSOR_(omegaSOR)
{
    
}

double SOR::iterate() const
{
    double factor = 0.5
        * (std::pow(discretization_->meshWidth_[0], 2) * std::pow(discretization_->meshWidth_[1], 2)) 
        / (std::pow(discretization_->meshWidth_[0], 2) + std::pow(discretization_->meshWidth_[1], 2));

    double residual = 0.0;

    // solve step
    for (int j = 1; j < discretization_->p.sizeY() - 1; ++j)
    {
        for (int i = 1; i < discretization_->p.sizeX() - 1; ++i)
        {
            discretization_->p(i,j) = (1-omegaSOR_) * discretization_->p(i,j)
                + omegaSOR_ * factor * ((discretization_->p(i-1,j) + discretization_->p(i+1,j)) 
                    / std::pow(discretization_->meshWidth_[0], 2)
                + (discretization_->p(i,j-1) + discretization_->p(i,j+1)) 
                    / std::pow(discretization_->meshWidth_[1], 2) 
                - discretization_->rhs(i,j));
        }
    }

    // calculate residual increment
    for (int j = 1; j < discretization_->p.sizeY() - 1; ++j)
    {
        for (int i = 1; i < discretization_->p.sizeX() - 1; ++i)
        {
            residual += std::pow(
                discretization_->rhs(i,j) 
                    - (discretization_->p(i-1,j) - 2 * discretization_->p(i,j) + discretization_->p(i+1,j)) 
                        / std::pow(discretization_->meshWidth_[0],2) 
                    - (discretization_->p(i,j-1) - 2 * discretization_->p(i,j) + discretization_->p(i,j+1)) 
                        / std::pow(discretization_->meshWidth_[1],2)
                ,2);
        }
    }
    
    return residual;
}
