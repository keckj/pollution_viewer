
#TODO Use cotire for eigen3

cmake_minimum_required(VERSION 2.8)

project(Visualization CXX)
set(VISUALIZATION_MAJOR_VERSION 0)
set(VISUALIZATION_MINOR_VERSION 1)
set(VISUALIZATION_PATCH_VERSION 0)
set(VISUALIZATION_VERSION ${VISUALIZATION_MAJOR_VERSION}.${VISUALIZATION_MINOR_VERSION}.${VISUALIZATION_PATCH_VERSION})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}")

find_package(Log4cpp REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(DevIL REQUIRED)
find_package(OpenMP)

#Compiler options
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message("-- Compiling for ${CMAKE_SYSTEM_NAME} with Clang...")
    set(CXX_FLAGS "-std=c++11 -m64")
    set(CXX_WERR "-Wall -Wextra -Wmissing-format-attribute -Wmissing-noreturn -Wredundant-decls -Wsequence-point -Wswitch-default -Wdeprecated -Wunreachable-code  -Wsign-conversion -Wold-style-cast -Wcovered-switch-default -Wmissing-variable-declarations -Wfloat-equal -Wunknown-warning-option")
    set(CXX_WNOERR "-Wno-weak-vtables -Wno-c++98-compat-pedantic -Wno-unused-parameter -Wno-deprecated-register -Wno-conversion -Wno-shadow -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors -Wno-source-uses-openmp -Wno-effc++")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message("-- Compiling for ${CMAKE_SYSTEM_NAME} with GCC...")
    set(CXX_FLAGS "-std=c++11 -m64")
    set(CXX_WERR "-Wall -Wextra -Wmissing-format-attribute -Wmissing-noreturn -Wredundant-decls -Wsequence-point -Wdeprecated -Wunreachable-code -Wold-style-cast -Wfloat-equal -Wsuggest-attribute=const -Wsuggest-attribute=pure")
    set(CXX_WNOERR "-Wno-unused-parameter -Wno-conversion -Wno-shadow -Wno-padded -Wno-effc++ -Wno-double-promotion -Wno-sign-conversion")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    message("-- Compiling for ${CMAKE_SYSTEM_NAME} with Intel C++...")
    message(WARNING "No custom compiler flags set for Intel C++...")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message("-- Compiling for ${CMAKE_SYSTEM_NAME} with Visual Studio C++...")
    message(WARNING "No custom compiler flags set for Visual Studio C++...")

endif()
    
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS} ${CXX_WERR} ${CXX_WNOERR} ${OpenMP_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} ")

# Better Stronger Faster Harder
# Work   it harder
# Make   it better
# Do     it faster
# Makes  us stronger
set(BUILD_SHARED_LIBS OFF)

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
    ${LOCAL_INCLUDE_DIRS}    #Local includes
    ${LOG4CPP_INCLUDE_DIRS}  #Log4cpp
    $[EIGEN3_INCLUDE_DIR}    #Eigen3 (template lib)
    ${IL_INCLUDE_DIR}        #DevIL
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
    ${LOG4CPP_LIBRARIES} #Log4cpp
    ${IL_LIBRARIES}      #DevIL core library
    #$[ILU_LIBRARIES}    #DevIL filters and effects
    #$[ILUT_LIBRARIES}   #DevIL interface with openGL
)



