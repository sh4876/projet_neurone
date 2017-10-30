cmake_minimum_required (VERSION 2.6)
project (Neurone)

set (CMAKE_CXX_FLAGS "-g -W -Wall -pedantic -std=c++11")
add_executable (neurone Neuron.cpp Excitatory.cpp Inhibitory.cpp Simulation.cpp main.cpp)

enable_testing()
add_subdirectory(gtest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable (neuron Neuron.cpp Excitatory.cpp Inhibitory.cpp Simulation.cpp main.cpp)
add_executable (neurone_unittest Neuron.cpp  Excitatory.cpp Inhibitory.cpp Simulation.cpp unittest.cpp)

target_link_libraries(neurone_unittest gtest gtest_main)
add_test(neurone_unittest neurone_unittest)

