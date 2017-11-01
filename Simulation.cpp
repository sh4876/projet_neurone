#include "Simulation.hpp"

#include "Neuron.hpp"
#include "Excitatory.hpp"
#include "Inhibitory.hpp"

#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include <random>

using namespace std;

//{}
// []

/**Constructor
 * @param total Number of neurone (NB_Neurones as default value)
 */
Simulation::Simulation(){
    CreateExcitatory();
    CreateInhibitory();
}


 /**RunSimulation
  * makes the connections between the neurones of the network
  * updates until the end of the simulation
  * @see main
  */
void Simulation::RunSimulation(int simulationEnd) {
		ConnectNetwork();
		UpdateSimulation(simulationEnd);

}

/**UpdateSimulation
 * check if the table of neurone is not empty
 * updates every neuron
 * if a neuron has a spike, an input is written in the buffer of it's targets
 * time of simulation incremented once each neuron has been updated once
 * @param step time at wich the simulation must end
 * @see RunSimulation
 */
void Simulation::UpdateSimulation (int SimulationEnd) {
    if (!Neurone.empty()) {
        int globalClock(0);
        while (globalClock < SimulationEnd) {

            for( size_t i(0); i<Neurone.size(); ++i) {
                if (Neurone[i] == nullptr) {cout << "pointeur nul" << endl;}

                ///update du neurone dans tous les cas
                else if (Neurone[i]->update() ) {
                    int atStepTime(Neurone[i]->getTimeSpike());
                    for (auto target : Neurone[i]->targets) {
                        target-> writeinBuffer(atStepTime);
                    }
                }
            }
        ++globalClock;
        cout << "global_clock" << globalClock*h << endl;
        }

    }
}

/**CreateConnection
 * neuron of index2 becomes a target of neuron of index1
 * @param indexes of two neurones in the table
 * @see ConnectNetwork
 */
void Simulation::CreateConnection(const size_t& index1, const size_t& index2) {
    assert(index1<Neurone.size());
    assert(index2<Neurone.size());
    if (index1 != index2) {
    (Neurone[index1]->targets).push_back(Neurone[index2]);}
 }

/**ConnectNetwork
 * generates the random connection between the neurons of the table
 * @see RunSimulation
 */
 void Simulation::ConnectNetwork() {
         random_device rd;
         mt19937 random_list (rd());
         uniform_int_distribution<> excitatory(0, NB_Excitatory-1);
         uniform_int_distribution<> inhibitory(NB_Excitatory, NB_Neurones-1);
         for (size_t target(0); target < NB_Neurones; ++target) {

                 for (size_t i(0); i < Ce; ++i) {
                        auto source(excitatory(random_list));
                        CreateConnection(source, target);
                        }
                for (size_t i(0); i < Ci; ++i) {
                        auto source(inhibitory(random_list));
                        CreateConnection(source, target);
                        }
        }
}


/**CreateExcitatory
 * generates a certain amount of excitatory neurones with external current
 * @param number of excitatory numbers whished, value of the external current (default value is I given in the constants file)
 * @see constructor
 */
void Simulation::CreateExcitatory () {
    for (int i(0); i < NB_Excitatory ; ++i) {
        Neurone.push_back(new Excitatory());
    }
}

/**CreateInhibitory
 * generates a certain amount of inhibitory neurones
 * @param number of inhibitory neurones whished, value of the external current (default value is I given in the constants file)
 * @see constructor
 */
void Simulation::CreateInhibitory () {
    for (int i(0); i < NB_Inhibitory ; ++i) {
        Neurone.push_back(new Inhibitory());
    }
}


                ///methods used in unittests

/**Connected
 * @param indexes of two neurones in the table
 * @see used in unittests
 * @return if neuron of index2 is a target of neuron of index1
 */
bool Simulation::Connected (const size_t& index1, const size_t& index2) const {
    for (const auto& target : Neurone[index1]->targets ) {
        if (target == Neurone[index2]) {return true;}
    }
    return false;
}

/**get_NbNeurones
 * @see used in unittests
 * @return number of neurones in the table
 */
unsigned int Simulation::get_NbNeurones () const {
    return Neurone.size();}

/**getNeuronePotential
 * @param index of the neurone of which we want to know the potential
 * @see used in unittests
 * @return potential of given neuron
 */
double Simulation::getNeuronePotential (size_t index) const {
    return Neurone[index]->getPotential(); }
