
cmake_minimum_required(VERSION 2.8)

project(Visualization CXX)
set(VISUALIZATION_MAJOR_VERSION 0)
set(VISUALIZATION_MINOR_VERSION 1)
set(VISUALIZATION_PATCH_VERSION 0)
set(VISUALIZATION_VERSION ${VISUALIZATION_MAJOR_VERSION}.${VISUALIZATION_MINOR_VERSION}.${VISUALIZATION_PATCH_VERSION})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}")

find_package(Boost COMPONENTS regex REQUIRED)
find_package(Log4cpp REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(DevIL REQUIRED)
find_package(Freetype REQUIRED)
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
    set(CXX_WERR "-Wall -Wextra -Wmissing-format-attribute -Wmissing-noreturn -Wredundant-decls -Wsequence-point -Wdeprecated -Wunreachable-code -Wold-style-cast -Wfloat-equal -Wno-suggest-attribute=const -Wno-suggest-attribute=pure -Wsign-conversion -Wdouble-promotion")
    set(CXX_WNOERR "-Wno-unused-parameter -Wno-unused-variable -Wno-conversion -Wno-shadow -Wno-padded -Wno-effc++")

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
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ")

#Compiler defines
set(COMPILER_DEFINES "-D_REENTRANT")
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug") 
    set(COMPILER_DEFINES "${COMPILER_DEFINES} -D_DEBUG -D_CONSOLE_LOG_LEVEL=DEBUG -D_FILE_LOG_LEVEL=DEBUG")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release") 
    set(COMPILER_DEFINES "${COMPILER_DEFINES} -D_CONSOLE_LOG_LEVEL=WARN -D_FILE_LOG_LEVEL=WARN")
else()
    set(COMPILER_DEFINES "${COMPILER_DEFINES} -D_CONSOLE_LOG_LEVEL=INFO -D_FILE_LOG_LEVEL=INFO")
endif()
add_definitions("${COMPILER_DEFINES}")

# Better Stronger Faster Harder
# Work  it harder
# Make  it better
# Do    it faster
# Makes us stronger
set(BUILD_SHARED_LIBS OFF)

#Project files
file(GLOB_RECURSE header_files src/*.hpp)
file(GLOB_RECURSE source_files src/*.cpp)
file(GLOB_RECURSE template_files src/*.tpp)

#Local includes
list(APPEND LOCAL_INCLUDE_DIRS "src/") #to avoid empty list
foreach(header ${header_files})
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND LOCAL_INCLUDE_DIRS ${dir})
endforeach()
list(REMOVE_DUPLICATES LOCAL_INCLUDE_DIRS)

#Header directories
include_directories(
    ${LOCAL_INCLUDE_DIRS}    #Local includes
    ${Boost_INCLUDEDIR}      #Boost
    ${LOG4CPP_INCLUDE_DIRS}  #Log4cpp
    ${EIGEN3_INCLUDE_DIR}    #Eigen3 (template lib)
    ${IL_INCLUDE_DIR}        #DevIL
    ${FREETYPE_INCLUDE_DIRS} #FreeType
)

#Library directories
link_directories(
    ${BOOST_LIBRARYDIR}
    ${LOG4CPP_LIBRARY_DIRS}
)

#Executables
add_executable(main ${header_files} ${source_files} ${template_files})

#Link executable
target_link_libraries(
    main 
    ${Boost_LIBRARIES}       #Boost Regex
    ${LOG4CPP_LIBRARIES}     #Log4cpp
    ${IL_LIBRARIES}          #DevIL core library
    ${ILU_LIBRARIES}         #DevIL filters and effects
    #${ILUT_LIBRARIES}       #DevIL interface with openGL
    ${FREETYPE_LIBRARIES}    #FreeType
)
