all: debug release

debug:
	g++ -std=c++11 -DDEBUG -Wall computation.cpp discretization/discretization.cpp discretization/centralDifferences.cpp settings/settings.cpp storage/array2d.cpp storage/fieldVariable.cpp discretization/staggeredGrid.cpp -g -o numsim_debug

release:
	g++ -std=c++11 -DDEBUG -Wall computation.cpp discretization/discretization.cpp discretization/centralDifferences.cpp settings/settings.cpp storage/array2d.cpp storage/fieldVariable.cpp discretization/staggeredGrid.cpp -Ofast -DNDEBUG -o numsim_release

clean:
	rm numsim_debug numsim_release
