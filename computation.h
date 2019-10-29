#pragma once

#include "settings/settings.h"
#include "discretization/staggeredGrid.h"
#include <vector>
#include <array>
#include <iostream>
#include <string>

/** This class represents the computation logic.
 */
class Computation
{
    private:

    Settings settings;

    std::array<double,2> computeMeshWidth();

public:

    Computation(std::string parameterFileName);
    void solve();

};
