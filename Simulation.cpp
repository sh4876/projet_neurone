#include "Simulation.hpp"

#include "Neuron.hpp"
#include "Excitatory.hpp"
#include "Inhibitory.hpp"

#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>

using namespace std;

//{}
// []

Simulation::Simulation(int NbNeurones){
	Neuron* n1(new Excitatory(1.01));
	Neuron* n2(new Excitatory(0,1.5));
	
	Neurone.push_back(n1);
	Neurone.push_back(n2);
	
	vector<bool> tabconnection(2, false);

	for (size_t i(0); i<2; ++i ) { 
		Connexions.push_back(tabconnection);
	}
}

void Simulation::RunSimulation() {
	int global_clock(STEP_SimulationStart);
	
	CreateConnection(0,1);
					
	UpdateSimulation(global_clock); 
	cout <<"      a2  "<< endl;
	
}

void Simulation::UpdateSimulation (int& globalClock) {
	if (!Neurone.empty()) {
		
		while (globalClock < STEP_SimulationStop) { 

			for( size_t i(0); i<Neurone.size(); ++i) {
				if (Neurone[i] == nullptr) {cout << "pointeur nul" << endl;}

				///update du neurone dans tous les cas 
				else if (Neurone[i]->update() ) {
					
					///on rentre dans cette boucle si le neurone a eu un spike
					///variable locale pour optimiser 
					///alors pour chaque neurone avec lequel il est connecté, on remplie la case correspondante du buffer
					int atStepTime(Neurone[i]->getTimeSpike()); 
					for (size_t j(0); j< Connexions.size(); ++j) {
						if( Connected(i,j)) { Neurone[j]->writeinBuffer(atStepTime);}
					}
				}
									
			}
				
			++globalClock;
			cout << "global_clock" << globalClock*h << endl;
		}
	}
}

void Simulation::CreateConnection(const size_t& index1, const size_t& index2) { /// index1=neurone presynaptique , index2 = neurone postsynaptique
	assert(index1<Connexions.size());
	assert(index2<Connexions[index1].size());
	if (index1 != index2 ) {
		Connexions[index1][index2] = true;} /// empeche qu un neurone soit connecte a lui meme
}

bool Simulation::Connected (const size_t& index1, const size_t& index2) const {
	assert(index1<Connexions.size());
	assert(index2<Connexions[index1].size());
	
	return Connexions[index1][index2];
}

unsigned int Simulation::get_NbNeurones () const {
	return Neurone.size();}
	
double Simulation::getNeuronePotential (size_t index) const {
	return Neurone[index]->getPotential(); }
