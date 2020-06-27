cmake_minimum_required(VERSION 3.16)
project(AiLabGeneticAlgorithm)

#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_EXTENSIONS OFF)
#set(CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main/main.cpp)

FILE(GLOB SRCFILES main/main.cpp string_matching/src/*.cpp nQueens/src/*.cpp
        genetic_solver/src/*.cpp general_utilities/src/*.cpp knap_sack/src/*.cpp
        bin_packing/src/*.cpp baldwin_effect/src/*.cpp nsga2/src/*.cpp optimal_xor/src/*.cpp)
#add_library(general_utilities general_utilities/src/OutputFileWriter.cpp)
#add_library(genetic_solver genetic_solver/src/AbstractGeneticSolver.cpp)
#add_library(nQueens nQueens/src/nQueensBoard.cpp nQueens/src/nQueensGenericSolver.cpp nQueens/src/nQueensGeneticSolver.cpp nQueens/src/nQueensMinimalConflictsSolver.cpp)
#add_library(string_matching string_matching/src/StringMatchingGeneticSolver.cpp string_matching/src/StringMatchingOutputFileWriter.cpp)
#add_executable(geneticString main/main.cpp)
ADD_EXECUTABLE(geneticString ${SRCFILES})
include_directories(genetic_solver/include/)
#find_library(general_utilities lib)
set_property(TARGET geneticString PROPERTY CXX_STANDARD 14)
