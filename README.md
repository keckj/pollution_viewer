Visualization
=============

Interpolation of sparse pollution data (PM10 particle concentrations) in the region of Grenoble and embedding into google earth.
The overlay is animated so that we can see daily evolution of particle pollution around Grenoble and Lyon.

## Screenshots (click to enlarge)
![pollution viewer](https://i.imgur.com/ni2JGKq.png)


Compilation
===========
```
mkdir build
cd build
cmake ..
```

Change build type:
`cmake -DCMAKE_BUILD_TYPE=Release ..`

Change cmake default compiler:

    1. Remove all cmake cache files and folders
    2. CXX=clang++ cmake ..

Dependancies
===========
CMake 2.8+ to generate the makefile.
A C++11 capable compiler for compilation.

Required libraries: Eigen, DevIL, Log4cpp, Freetype2, Boost (Regex)

Tested with CMake 2.8, gcc 4.8.2 and clang 3.5.
You might need to provide specific flags for exotic compilers in the CMakeList.txt present at the root of the project in order to compile C++11.

Running the project
===================
At the root of the project, execute with ./main
All files that are generated are in the folder kml/
root.kml is the generated kml file, you can open it directly in google-earth.
Subfolders contain images that are loaded by the kml file in google-earth.

