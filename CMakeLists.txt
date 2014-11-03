
cmake_minimum_required(VERSION 2.8)

project(Visualization CXX)
set(VISUALIZATION_MAJOR_VERSION 0)
set(VISUALIZATION_MINOR_VERSION 1)
set(VISUALIZATION_PATCH_VERSION 0)
set(VISUALIZATION_VERSION ${VISUALIZATION_MAJOR_VERSION}.${VISUALIZATION_MINOR_VERSION}.${VISUALIZATION_PATCH_VERSION})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}")

set(BUILD_SHARED_LIBS OFF)

find_package(Log4cpp REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(DevIL REQUIRED)

set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Wno-unused-parameter -pedantic -std=c++11 -m64")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_EXE_LINKER_FLAGS "-O2")

#Project files
file(GLOB_RECURSE header_files src/*.h)
file(GLOB_RECURSE source_files src/*.cpp)
file(GLOB_RECURSE template_files src/*.tpp)
file(GLOB_RECURSE data_files data/*.kml)

#Local includes
foreach(header ${header_files})
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND LOCAL_INCLUDE_DIRS ${dir})
endforeach()
if(${LOCAL_INCLUDE_DIRS})
    list(REMOVE_DUPLICATES LOCAL_INCLUDE_DIRS)
endif()

#Header directories
include_directories(
    ${LOCAL_INCLUDE_DIRS}    //Local include folders
    ${LOG4CPP_INCLUDE_DIRS}  //Log4cpp
    $[EIGEN3_INCLUDE_DIR}    //Eigen3 (template lib)
    ${IL_INCLUDE_DIR}        //DevIL
)

#Library directories
link_directories(
    ${LOG4CPP_LIBRARY_DIRS}
)

#Executables
add_executable(main ${header_files} ${source_files} ${template_files})

#Link executable
target_link_libraries(
    main 
    ${LOG4CPP_LIBRARIES} //Log4cpp
    $[IL_LIBRARIES}      //DevIL core library
    //$[ILU_LIBRARIES}   //DevIL filters and effect
    //$[ILUT_LIBRARIES}  //DevIL interface with openGL
)



