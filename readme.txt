-----------------------------------
---- Readme for numsim project ----
-----------------------------------

- Before making the executable the first time, create build directory 
- and go to ./build and execute
    $ cmake ..

- To make a new executable type
    $ make install

- To run the executable got to ./build and run
    $ ./numsim ./parameters.txt

- To add new source files to cmake go to ./src/CMakeLists.txt and edit the part
     ...
     add_executable( ...
        ...
        newSource.cpp
     )

