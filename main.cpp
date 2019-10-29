void testSettings()
{
    Settings settings;
    settings.loadFromFile("parameters.txt");
    settings.printSettings();
}

void testStaggeredGrid()
{
    Settings settings;
    settings.loadFromFile("parameters.txt");

    // compute meshWidth


    StaggeredGrid grid({ settings.nCells[0] + 2, settings.nCells[1] + 2 }, meshWidth);

    grid.u(1,1) = 6.0;
    grid.u(2,1) = 7.0; 
    grid.u(1,2) = 10.0; 
    grid.u(2,2) = 11.0; 

    grid.u.print();
    std::cout << std::endl << std::endl;
    grid.setUVBoundaries(settings.dirichletBcBottom, settings.dirichletBcTop, settings.dirichletBcLeft, settings.dirichletBcRight);
    grid.u.print();
}

int main(int argc, char *argv[]) 
{
    testStaggeredGrid();
}