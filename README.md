Visualization
=============

Ensimag visualization project

Compilation
===========
mkdir build
cd build
cmake ..

Change build type:
    cmake -D_CMAKE_BUILD_TYPE={Debug/Release} ..

Change cmake default compiler:
    1) Remove all cmake cache files and folders
    2) CXX=clang++ cmake ..

Dependancies
===========
CMake 2.8+ to generate the makefile.
A C++11 capable compiler for compilation.

Libraries: Eigen, DevIL, Log4cpp, Freetype2, Boost (Regex)
Optional: OpenMP capable compiler, Cuda (not implemented yet)

Tested with CMake 2.8, gcc 4.8.2 and clang 3.5.
You might need to provide specific flags for exotic compilers in the CMakeList.txt present at the root of the project in order to compile C++11.

Running Project
===========
At the root of the project, execute with ./main
All files that are generated are in the folder kml/
root.kml is the generated kml file, you can open it in google-earth.
Subfolders contain images that are loaded by the kml file in google-earth.

