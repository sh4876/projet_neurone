#include "Neuron.hpp"
#include "Constants.hpp"
#include <iostream>

void Neuron::storePotential (ofstream PotentialStorage) const {
	PotentialStorageFile<< getTimeSpike() << " " << getPotential() << endl;}
	
double Neuron::getPotential() const {
	return potential;}

int Neuron::getSpikeNumber() const {
	return spikeNumber;}
	
double Neuron::getTimeSpike() const {
	return timeSpike;}

Neuron::Neuron(double pot=0.0, int spike=0, double time=0 ) : potential(pot), spikeNumber(spike), timeSpike(time) {} 

void Neuron::update ( int increment) {
	double cst(exp(-increment*h/tau));
	potential = cst*potential + I*R*(1-cst);
	}
