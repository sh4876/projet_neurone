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
	
	void update ( int increment) ;
	void storePotential (ofstream PotentialStorage) const; 
	
	public :
	Neuron(double, int, double);
	double getPotential() const;
	int getSpikeNumber() const;
	double getTimeSpike() const;
	};
	

#endif
