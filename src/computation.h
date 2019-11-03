#pragma once

#include "settings/settings.h"
#include "discretization/discretization.h"
#include "discretization/centralDifferences.h"
#include "discretization/donorCell.h"
#include "pressureSolver/pressureSolver.h"
#include "pressureSolver/gaussSeidel.h"
#include "pressureSolver/sor.h"
#include "outputWriter/outputWriter.h"
#include "outputWriter/outputWriterParaview.h"
//#include "outputWriter/outputWriterText.h"
#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <memory>

/** This class represents the computation logic.
 */
class Computation
{
    private:

    Settings settings_;
    std::shared_ptr<Discretization> discretization_;
    std::shared_ptr<PressureSolver> pressureSolver_;
    std::shared_ptr<OutputWriter> outputWriter_;
    std::array<double,2> meshWidth_;
    double dt_;

    void computeMeshWidth();
    void computeTimeStepWidth();

    //! compute and set the F and G field
    void computePreliminaryVelocities();

    //! compute and set the boundary cells of F and G
    void computePreliminaryVelocitiesBoundary();

    //! compute and set the RHS field
    void computerightHandSide();

    //! sets/updates the boundaries for the pressure field p
    void computePressureBoundaries();

    //! sets/updates the boundaries for the velocity fields u and v
    void computeVelocityBoundaries();

    void computeNewVelocities();

public:

    Computation(std::string parameterFileName);
    
    void testDiscretization();
    void testSettings();
    void testTimestep();
    void testInterpolation();

    void runSimulation();
};