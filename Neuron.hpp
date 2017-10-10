#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include "Constants.hpp"

using namespace std;
//{}



class Neuron {
	
	private :
	double potential;
	int spikeNumber;
	double timeSpike;
	double local_clock;
	
	bool isRefractory(const double&) const; //dit si le neurone est en periode refractaire a un temps donné

	void storePotential (ofstream& out ) const; 
	
	public :
	Neuron(double pot=Vr, int spike=0, double timeofSpike=0.0, double timeofSimulation= SimulationStart); // initialisation
	double getPotential() const;
	int getSpikeNumber() const;
	double getTimeSpike() const;
	
	void update () ; 
};
	

#endif
