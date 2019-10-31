all: debug release

debug:
	g++ -std=c++11 -DDEBUG -Wall main.cpp computation.cpp pressureSolver/pressureSolver.cpp pressureSolver/sor.cpp pressureSolver/gaussSeidel.cpp discretization/discretization.cpp discretization/centralDifferences.cpp discretization/donorCell.cpp settings/settings.cpp storage/array2d.cpp storage/fieldVariable.cpp discretization/staggeredGrid.cpp -g -o numsim_debug

release:
	g++ -std=c++11 -DDEBUG -Wall main.cpp computation.cpp pressureSolver/pressureSolver.cpp pressureSolver/sor.cpp pressureSolver/gaussSeidel.cpp discretization/discretization.cpp discretization/centralDifferences.cpp discretization/donorCell.cpp settings/settings.cpp storage/array2d.cpp storage/fieldVariable.cpp discretization/staggeredGrid.cpp -Ofast -DNDEBUG -o numsim_release

clean:
	rm numsim_debug numsim_release
