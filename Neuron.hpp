#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>
#include <fstream>
using namespace std;
//{}
ofstream PotentialStorageFile ("potentials.txt", ios::app); // ios::out ׀ 


class Neuron {
	
	private :
	double potential;
	int spikeNumber;
	double timeSpike;
	double local_clock;
	
	bool isRefractory(double) const; //dit si le neurone est en periode refractaire a un temps donné
	void storePotential () const; 
	
	public :
	Neuron(double, int, double, double); // initialisation
	double getPotential() const;
	int getSpikeNumber() const;
	double getTimeSpike() const;
	
	void update () ; 
	};
	

#endif
