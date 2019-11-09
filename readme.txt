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

Helpfull things:

Link for excercise  https://numsim-exercises.readthedocs.io/en/latest/
Link for abgaben    http://opendihu-ci/?icansubmit (abgabe immer möglich)
respectivly         http://129.69.213.149/?icansubmit

without the ?icansubmit there is the normal time limit.


Zip for abgaben     zip -r submission.zip src/ CMakeLists.txt
