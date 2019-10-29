#include "computation.h"

Computation::Computation(std::string parameterFileName) : settings()
{
    settings.loadFromFile(parameterFileName);
}

std::array<double,2> Computation::computeMeshWidth()
{
    double dx = settings.physicalSize[0] / settings.nCells[0];
    double dy = settings.physicalSize[1] / settings.nCells[1];
    return { dx, dy };
}

void Computation::solve()
{   
    // test p field variable
    if (false)
    {
        StaggeredGrid grid({ settings.nCells[0] + 2, settings.nCells[1] + 2 }, computeMeshWidth());

        grid.p(1,1) = 6.0;
        grid.p(2,1) = 7.0; 
        grid.p(1,2) = 10.0; 
        grid.p(2,2) = 11.0; 

        grid.p.print();
        std::cout << std::endl << std::endl;
        grid.setPBoundaries();
        //grid.setUVBoundaries(settings.dirichletBcBottom, settings.dirichletBcTop, settings.dirichletBcLeft, settings.dirichletBcRight);
        grid.p.print();
    }

    // test u field variable
    {
        StaggeredGrid grid({ settings.nCells[0] + 2, settings.nCells[1] + 2 }, computeMeshWidth());

        grid.v(1,1) = 2.0;
        grid.v(2,1) = 4.0; 
        grid.v(1,2) = 6.0; 
        grid.v(2,2) = 8.0; 

        grid.v.print();
        std::cout << std::endl << std::endl;
        grid.setUVBoundaries(settings.dirichletBcBottom, settings.dirichletBcTop, settings.dirichletBcLeft, settings.dirichletBcRight);
        grid.v.print();
    }
}

int main(int argc, char *argv[]) 
{
    Computation comp("parameters.txt");
    comp.solve();
}