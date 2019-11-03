-----------------------------------
---- Readme for numsim project ----
-----------------------------------

- Before making the executable the first time, go to ./build and execute
    $ cmake ..

- To make a new executable type
    $ make install

- To run the executable got to ./build, add a parameter.txt file and run
    $ ./numsim 

- To add new source files to cmake go to ./src/CMakeLists.txt and edit the part
     ...
     add_executable( ...
        ...
        newSource.cpp
     )

