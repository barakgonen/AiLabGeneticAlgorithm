cmake_minimum_required(VERSION 3.16)
project(AiLabGeneticAlgorithm)

set(CMAKE_C_STANDARD 11)
FILE(GLOB SRCFILES main/main.cpp string_matching/src/*.cpp nQueens/src/*.cpp genetic_solver/src/*.cpp general_utilities/src/*.cpp)
ADD_EXECUTABLE(geneticString ${SRCFILES})