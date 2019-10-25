all: debug release

debug:
	g++ -std=c++11 computation.cpp settings.cpp storage/array2d.cpp storage/fieldVariable.cpp storage/staggeredGrid.cpp -g -o numsim_debug

release:
	g++ -std=c++11 computation.cpp settings.cpp storage/array2d.cpp storage/fieldVariable.cpp storage/staggeredGrid.cpp -Ofast -DNDEBUG -o numsim_release

clean:
	rm numsim_debug numsim_release
