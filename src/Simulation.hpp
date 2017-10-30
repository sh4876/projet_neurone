#ifndef SIMULATION_HPP
#define SIMULATION_HPP



#include <iostream>
#include <cmath>
#include <vector>

#include "Constants.hpp"


using namespace std;

typedef vector<vector<bool>> Tableconnexion;
//typedef vector<vector<size_t>> Tableconnexion;

class Neuron;
class Inhibitory;
class Excitatory;

class Simulation {
	
	private:
vector<Neuron*> Neurone; 		//!< saves all the neuron involved in the simulation
Tableconnexion Connexions; 		//!< saves for each neuron the index of the neurons it is connected to 

	public :
Simulation(int NbNeurones= 2); 		//!< constuctor
void RunSimulation(); 				//!< runs the simulation
void UpdateSimulation (int& globalClock); 	//!< updates simulation from globalClock until SimulationEnd
void CreateConnection(const size_t& index1, const size_t& index2); //!< creates connections between two neurones 
 // void Simulation::ConnectNetwork() ; //!< randomly connects the whole network
bool Connected (const size_t& index1, const size_t& index2) const; //unecessary
unsigned int get_NbNeurones () const ; //!< return number of neuron in the simulation
double getNeuronePotential(size_t index) const; //utile pour les tests 
	
	};



//eventuellement faire une methode qui ajoute des neurones


#endif

