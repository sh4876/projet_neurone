#ifndef SIMULATION_HPP
#define SIMULATION_HPP



#include <iostream>
#include <cmath>
#include <vector>

#include "Constants.hpp"


using namespace std;

typedef vector<vector<bool>> Tableconnexion;

class Neuron;

class Simulation {
	
	private:
vector<Neuron*> Neurone;
Tableconnexion Connexions;

	public :
Simulation(int NbNeurones= 2); 	
void RunSimulation();
void UpdateSimulation (int& globalClock); 
void CreateConnection(const size_t& index1, const size_t& index2);
bool Connected (const size_t& index1, const size_t& index2) const;
unsigned int get_NbNeurones () const ; 
double getNeuronePotential(size_t index) const; 
	
	};



//eventuellement faire une methode qui ajoute des neurones


#endif

