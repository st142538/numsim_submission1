#include "computation.h"

void Computation::computeMeshWidth()
{
    double dx = settings_.physicalSize[0] / settings_.nCells[0];
    double dy = settings_.physicalSize[1] / settings_.nCells[1];
    meshWidth_ = { dx, dy };
}

void Computation::computeTimeStepWidth()
{

}

Computation::Computation(std::string parameterFileName) : settings_()
{
    settings_.loadFromFile(parameterFileName);
    computeMeshWidth();

    std::array<int,2> nCellsWithBoundary = { settings_.nCells[0] + 2, settings_.nCells[1] + 2 };

    if (settings_.discretizationType == "CD")
    {
        discretization_ = std::make_shared<CentralDifferences>(nCellsWithBoundary, meshWidth_);
    }
    else
    {
        discretization_ = std::make_shared<DonorCell>(nCellsWithBoundary, meshWidth_, settings_.alphaDC);
    }
}

void Computation::computePreliminaryVelocities()
{
    // calculate helper variable A and set F
    for (int j = 1; j < discretization_->u.sizeY() - 1; ++j)
    {
        for (int i = 1; i < discretization_->u.sizeX() - 1; ++i)
        {
            double A = (discretization_->computeD2uDx2(i,j) + discretization_->computeD2uDy2(i,j)) / settings_.re - discretization_->computeDu2Dx(i,j) - discretization_->computeDuvDy(i,j) + settings_.g[0];
            discretization_->f(i,j) = discretization_->u(i,j) + dt_ * A;
        }
    }

    // calculate helper variable B and set G
    for (int j = 1; j < discretization_->v.sizeY() - 1; ++j)
    {
        for (int i = 1; i < discretization_->v.sizeX() - 1; ++i)
        {
            double B = (discretization_->computeD2vDx2(i,j) + discretization_->computeD2vDy2(i,j)) / settings_.re - discretization_->computeDv2Dy(i,j) - discretization_->computeDuvDx(i,j) + settings_.g[1];
            discretization_->g(i,j) = discretization_->v(i,j) + dt_ * B;
        }
    }
}

void Computation::computerightHandSide()
{
    for (int j = 1; j < discretization_->p.sizeY() - 1; ++j)
    {
        for (int i = 1; i < discretization_->p.sizeX() - 1; ++i)
        {
            discretization_->rhs(i,j) = (((discretization_->f(i,j) - discretization_->f(i-1,j)) / meshWidth_[0]) + ((discretization_->g(i,j) - discretization_->g(i,j-1)) / meshWidth_[1])) / dt_;
        }
    }
}

void Computation::computePressureBoundaries()
{
    // set the 4 corner boundary cells
    discretization_->p(0, 0) 
        = discretization_->p(1, 1);                                                             // bottom left
    discretization_->p(discretization_->p.sizeX() - 1, 0) 
        = discretization_->p(discretization_->p.sizeX() - 2, 1);                                // bottom right
    discretization_->p(0, discretization_->p.sizeY() - 1) 
        = discretization_->p(1, discretization_->p.sizeY() - 2);                                // top left
    discretization_->p(discretization_->p.sizeX() - 1, discretization_->p.sizeY() - 1) 
        = discretization_->p(discretization_->p.sizeX() - 2, discretization_->p.sizeY() - 2);   // top right

    // set the top and bottom boundaries edges except corner cells
    for (int i = 1; i < discretization_->p.sizeX() - 1; ++i)
    {
        discretization_->p(i, 0) 
            = discretization_->p(i, 1);                                 // bottom
        discretization_->p(i, discretization_->p.sizeY() - 1) 
            = discretization_->p(i, discretization_->p.sizeY() - 2);    // top
    }

    // set the left and right boundaries edges except corner cells
    for (int j = 1; j < discretization_->p.sizeY() - 1; ++j)
    {
        discretization_->p(0, j) 
            = discretization_->p(1, j);                                 // left
        discretization_->p(discretization_->p.sizeX() - 1, j) 
            = discretization_->p(discretization_->p.sizeX() - 2, j);    // right
    }
}

void Computation::computeVelocityBoundaries()
{
    // set the left and right boundary edge for u (velocity in x direction)
    // except the corner cells
    for (int j = 1; j < discretization_->u.sizeY() - 1; ++j)
    {
        discretization_->u(0, j) 
            = settings_.dirichletBcLeft[0];
        discretization_->u(discretization_->u.sizeX() - 1, j) 
            = settings_.dirichletBcRight[0];
    }
    // set the bottom and top boundary edge for u (velocity in x direction)
    // with the corner cells
    for (int i = 0; i < discretization_->u.sizeX(); ++i)
    {
        discretization_->u(i, 0) 
            = 2 * settings_.dirichletBcBottom[0] - discretization_->u(i, 1);
        discretization_->u(i, discretization_->u.sizeY() - 1) 
            = 2 * settings_.dirichletBcTop[0] - discretization_->u(i, discretization_->u.sizeY() - 2);
    }

    // set the bottom and top boundary edge for v (velocity in y direction)
    // except the corner cells
    for (int i = 1; i < discretization_->v.sizeX() - 1; ++i)
    {
        discretization_->v(i, 0) 
            = settings_.dirichletBcBottom[1];
        discretization_->v(i, discretization_->v.sizeY() - 1) 
            = settings_.dirichletBcTop[1];
    }

    // set the left and right boundary edge for v (velocity in y direction)
    // with the corner cells
    for (int j = 0; j < discretization_->v.sizeY(); ++j)
    {
        discretization_->v(0, j) 
            = 2 * settings_.dirichletBcLeft[1] - discretization_->v(1, j);
        discretization_->v(discretization_->v.sizeX() - 1, j) 
            = 2 * settings_.dirichletBcRight[1] - discretization_->v(discretization_->v.sizeX() - 2, j);
    }
}

void Computation::runSimulation()
{   
    // test p field variable
    if (false)
    {        
        discretization_->p(1,1) = 6.0;
        discretization_->p(2,1) = 7.0; 
        discretization_->p(1,2) = 10.0; 
        discretization_->p(2,2) = 11.0; 

        discretization_->p.print();
        std::cout << std::endl << std::endl;
        computePressureBoundaries();
        discretization_->p.print();
    }

    // test v field variable
    {
        discretization_->v(1,1) = 2.0;
        discretization_->v(2,1) = 4.0; 
        discretization_->v(1,2) = 6.0; 
        discretization_->v(2,2) = 8.0; 

        discretization_->v.print();
        std::cout << std::endl << std::endl;
        computeVelocityBoundaries();
        discretization_->v.print();
    }
}

int main(int argc, char *argv[]) 
{
    Computation computation("parameters.txt");
    computation.runSimulation();
}