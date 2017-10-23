cmake_minimum_required (VERSION 2.6)
project (Neurone)

set (CMAKE_CXX_FLAGS "-g -W -Wall -pedantic -std=c++11")
add_executable (neurone Neuron.cpp Simulation.cpp main.cpp)

