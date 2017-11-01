#ifndef SIMULATION_HPP
#define SIMULATION_HPP



#include <iostream>
#include <cmath>
#include <vector>

#include "Constants.hpp"


using namespace std;


class Neuron;
class Inhibitory;
class Excitatory;

class Simulation {

        private:
vector<Neuron*> Neurone;                //!< saves all the neuron involved in the simulation
void CreateExcitatory () ;
void CreateInhibitory () ;
   


        public :
Simulation();          //!< constuctor
void RunSimulation(int simulationEnd = STEP_SimulationStop);                           //!< runs the simulation
void UpdateSimulation (int simulationEnd);       //!< updates simulation from globalClock until SimulationEnd
void CreateConnection(const size_t& index1, const size_t& index2); //!< creates connections between two neurones
void ConnectNetwork() ; //!< randomly connects the whole network
bool Connected (const size_t& index1, const size_t& index2) const; //unecessary
unsigned int get_NbNeurones () const ; //!< return number of neuron in the simulation
double getNeuronePotential(size_t index) const; //utile pour les tests

        };



//eventuellement faire une methode qui ajoute des neurones


#endif
