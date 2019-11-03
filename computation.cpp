#include "computation.h"
Computation::Computation(std::string parameterFileName) : settings_()
{
    settings_.loadFromFile(parameterFileName);
    computeMeshWidth();

    std::array<int,2> nCellsWithBoundary = { settings_.nCells[0] + 2, settings_.nCells[1] + 2 };

    // set dt_ to maximumDt
    dt_ = settings_.maximumDt;

    // instantiate the discretization
    if (settings_.discretizationType == "CD")
    {
        discretization_ = std::make_shared<CentralDifferences>(nCellsWithBoundary, meshWidth_);
    }
    else // means DC
    {
        discretization_ = std::make_shared<DonorCell>(nCellsWithBoundary, meshWidth_, settings_.alphaDC);
    }

    // instatiate the pressure solver
    if (settings_.discretizationType == "GaussSeidel")
    {
        pressureSolver_ = std::make_shared<GaussSeidel>(discretization_);
    }
    else // means SOR
    {
        pressureSolver_ = std::make_shared<SOR>(discretization_, settings_.omegaSOR);
    }

    // instatiate the pressure solver
    outputWriter_ = std::make_shared<outputWriterParaview>(discretization_);
}

void Computation::computeMeshWidth()
{
    double dx = settings_.physicalSize[0] / settings_.nCells[0];
    double dy = settings_.physicalSize[1] / settings_.nCells[1];
    meshWidth_ = { dx, dy };
}

void Computation::computeTimeStepWidth()
{
    // TODO Notation
    // compute all four upper limits for the time step width
    double upper_limit1 = 0.5 
        * settings_.re 
        * std::pow(meshWidth_[0]*meshWidth_[1],2) 
        / (std::pow(meshWidth_[0],2) + std::pow(meshWidth_[1],2));
    double max_abs_u = std::max(std::abs(discretization_->u.min()), std::abs(discretization_->u.max()));
    double max_abs_v = std::max(std::abs(discretization_->v.min()), std::abs(discretization_->v.max()));
    double upper_limit2 = meshWidth_[0] / max_abs_u;
    double upper_limit3 = meshWidth_[1] / max_abs_v;
    double upper_limit4 = settings_.maximumDt;

    // TODO min auf alle elemente
    // set the time step width to the minimum of all four possibilities times safety factor tau
    dt_ = settings_.tau * std::min( std::min(upper_limit1,upper_limit2), std::min(upper_limit3, upper_limit4) );
}



void Computation::computePreliminaryVelocities()
{
    // calculate helper variable A and set F for inner points
    for (int j = 1; j < discretization_->f.sizeY() - 1; ++j)
    {
        for (int i = 1; i < discretization_->f.sizeX() - 1; ++i)
        {
            double A = (discretization_->computeD2uDx2(i,j) + discretization_->computeD2uDy2(i,j)) / settings_.re 
                - discretization_->computeDu2Dx(i,j) 
                - discretization_->computeDuvDy(i,j) 
                + settings_.g[0];
            discretization_->f(i,j) = discretization_->u(i,j) + dt_ * A;
        }
    }

    // calculate helper variable B and set G for inner points
    for (int j = 1; j < discretization_->g.sizeY() - 1; ++j)
    {
        for (int i = 1; i < discretization_->g.sizeX() - 1; ++i)
        {
            double B = (discretization_->computeD2vDx2(i,j) + discretization_->computeD2vDy2(i,j)) / settings_.re 
                - discretization_->computeDv2Dy(i,j) 
                - discretization_->computeDuvDx(i,j) 
                + settings_.g[1];
            discretization_->g(i,j) = discretization_->v(i,j) + dt_ * B;
        }
    }
}

void Computation::computePreliminaryVelocitiesBoundary()
{
    // calculate helper variable A and set F for boundary points
    for (int j = 0; j < discretization_->f.sizeY(); ++j)
    {
        discretization_->f(0,j) = settings_.dirichletBcLeft[0];
        discretization_->f(discretization_->f.sizeX() - 1,j) = settings_.dirichletBcRight[0];
    }

    // calculate helper variable B and set G for boundary points
    for (int i = 0; i < discretization_->g.sizeX(); ++i)
    {
        discretization_->g(i,0) = settings_.dirichletBcBottom[1];
        discretization_->g(i,discretization_->g.sizeY() - 1) = settings_.dirichletBcTop[1];
    }
}

void Computation::computerightHandSide()
{
    for (int j = 1; j < discretization_->p.sizeY() - 1; ++j)
    {
        for (int i = 1; i < discretization_->p.sizeX() - 1; ++i)
        {
            discretization_->rhs(i,j) = 
                (((discretization_->f(i,j) 
                - discretization_->f(i-1,j)) / meshWidth_[0]) 
                + ((discretization_->g(i,j) 
                - discretization_->g(i,j-1)) / meshWidth_[1])) / dt_;
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

void Computation::computeNewVelocities()
{
    for (int j = 1; j < discretization_->u.sizeY() - 1; ++j)
    {
        for (int i = 1; i < discretization_->u.sizeX() - 1; ++i)
        {
            discretization_->u(i,j) = discretization_->f(i,j) - dt_ * discretization_->computeDpDx(i, j);
        }
    }

    for (int j = 1; j < discretization_->v.sizeY() - 1; ++j)
    {
        for (int i = 1; i < discretization_->v.sizeX() - 1; ++i)
        {
            discretization_->v(i,j) = discretization_->g(i,j) - dt_ * discretization_->computeDpDy(i, j);
        }
    }
}

void Computation::testDiscretization()
{
    // test p field variable
    {        
        discretization_->p(1,1) = 1.0;
        discretization_->p(2,1) = 2.0; 
        discretization_->p(1,2) = 3.0; 
        discretization_->p(2,2) = 4.0; 

        discretization_->p.print();
        std::cout << std::endl << std::endl;
        computePressureBoundaries();
        discretization_->p.print();
        std::cout << std::endl << std::endl;
    }

    // test u field variable
    {
        discretization_->u(1,1) = 2.0;
        discretization_->u(2,1) = 4.0; 
        discretization_->u(1,2) = 6.0; 
        discretization_->u(2,2) = -50.0; 

        discretization_->u.print();
        std::cout << std::endl << std::endl;
        computeVelocityBoundaries();
        discretization_->u.print();
        std::cout << std::endl << std::endl;
    }

    // test array2D max(), min()
    {
        std::cout << "max(p) = " << discretization_->p.max() << std::endl;
        std::cout << "max(u) = " << discretization_->u.max() << std::endl;
        std::cout << "min(u) = " << discretization_->u.min() << std::endl;
        std::cout << "max(|u|) = " << std::max(std::abs(discretization_->u.min()), std::abs(discretization_->u.max())) << std::endl;
    }
}

void Computation::testSettings()
{
    settings_.printSettings();
}

void Computation::testTimestep()
{
    std::cout << "previous dt: " << dt_ << std::endl;
    computeTimeStepWidth();
    std::cout << "new dt: " << dt_ << std::endl;
}

void Computation::testInterpolation()
{
    discretization_->u(1,1) = 1.0;
    discretization_->u(2,1) = 2.0; 
    discretization_->u(1,2) = 1.0; 
    discretization_->u(2,2) = 2.0; 
    discretization_->u.print();
    std::cout << "test: " << discretization_->u.interpolateAt(0.5*meshWidth_[0], 0.75*meshWidth_[1]) << std::endl;
}

void Computation::runSimulation()
{   
    double currentTime = 0.0;
    int step = 0;
    while (currentTime < settings_.endTime) {
        computeTimeStepWidth();
        computeVelocityBoundaries();
        computePressureBoundaries();
        computePreliminaryVelocities();
        computePreliminaryVelocitiesBoundary();
        computerightHandSide();
        int it = 0;
        double squared_residual = 1.0 / 0.0;
        while ((it < settings_.maxPressureIterations) || (std::sqrt(squared_residual) > settings_.epsilonTol)) {
            squared_residual = pressureSolver_->iterate();
            computePressureBoundaries();
            it++;
        }
        computeNewVelocities();
        currentTime += dt_;
        step++;
        // print time step information
        std::cout << step 
                << " dt: " << dt_ 
                << ", current time: " << currentTime 
                << ", pressure solver iterations: " << it << std::endl;

    }
    computeVelocityBoundaries();
    computePressureBoundaries();
}

