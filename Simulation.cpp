#include "Simulation.hpp"

#include "Neuron.hpp"

#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>

using namespace std;
//{}
// []

Simulation::Simulation(int NbNeurones){
	Neuron* n1(new Neuron(0));
	Neuron* n2(new Neuron(I,0));
	Neurone.push_back(n1);
	Neurone.push_back(n2);
	
	vector<bool> tabconnection(2, false);

	for (size_t i(0); i<2; ++i ) { 
		Connexions.push_back(tabconnection);
	}
	
		
}

void Simulation::RunSimulation() {
	int global_clock(STEP_SimulationStart);
	cout << "global_clock" << global_clock *h << endl;
	
	while (global_clock<STEP_SimulationStop) {
		/// l utilisateur choisit de combien de pas de temps il veut avancer la simulation--------------------------
		int increment=0;
		double tmp=0.0;
		int borneSup((STEP_SimulationStop-global_clock));
		cout <<" choisir l increment tq 0 < increment < "<< borneSup << endl;
		cin>> tmp;
		increment=(int)tmp;
		
			if ((increment>borneSup)or(increment <0)) 
				{cout <<"exit erreur d increment "<< endl; }
				
			// : Floating point exception
			
			
			/// si l increment rentré est bon, poursuite de la simulation
			else 
				{ 	
					
					CreateConnection(0,1);
					
					UpdateSimulation(global_clock, increment); }
					cout <<"      a2  "<< endl;
	}
}

void Simulation::UpdateSimulation (int& globalClock, int increment) {
	if (!Neurone.empty()) {
		int finUpdate(globalClock+increment); ///in step time
		
		/// update seuleument jusqu au temps choisit par l utilisateur qui ne correspond pas forcement a la fin de la simulation 
		while (globalClock < finUpdate) { 

			
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

size_t Simulation::get_NbNeurones () const {
	return Neurone.size();}
	
double Simulation::getNeuronePotential (size_t index) const {
	return Neurone[index]->getPotential(); }
