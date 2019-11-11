-----------------------------------
==== Readme for numsim project ====
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

Helpful things:

Link for excercise  https://numsim-exercises.readthedocs.io/en/latest/
Link for abgaben    http://opendihu-ci/?icansubmit (abgabe immer möglich)
respectivly         http://129.69.213.149/?icansubmit

without the ?icansubmit there is the normal time limit.

Zip for submissions:     zip -r submission.zip src/ CMakeLists.txt

------------------------------------------------
==== Comments on submission for exercise 1: ====

Wanted Bugs in submission for exercise 1:

- no set f,g - preliminary velocity boundary in simulation loop, f,g = 0 at boundary
- no reset of u,v-velocity boundary in simulation loop
- length of v-related loops in computeVelocityBoundaries() unclear, lr longer is wanted

Reference solution weirdness:

- order of computeVelocityBoundaries(), computePressureBoundaries(), computeTimeStepWidth() was wrong
- residual abort condition was not clear
