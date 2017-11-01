#include <iostream>
#include <cmath>
#include <vector>
#include "Neuron.hpp"
#include "Constants.hpp"
#include "Simulation.hpp"

using namespace std;
//{}
// []



int main (){

    Simulation S1(5,2);
    S1.RunSimulation();
    S1.writeSpikeInFile("spikes.txt");


    return 0;
}



