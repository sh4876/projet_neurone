#include "Neuron.hpp"
#include "Constants.hpp"
#include <iostream>


void Neuron::storePotential () const {
	PotentialStorageFile<< getTimeSpike() << " " << getPotential() << endl;}
	
double Neuron::getPotential() const {
	return potential;}

int Neuron::getSpikeNumber() const {
	return spikeNumber;}
	
double Neuron::getTimeSpike() const {
	return timeSpike;}

Neuron::Neuron(double pot=Vr, int spike=0, double time=0.0 ) : potential(pot), spikeNumber(spike), timeSpike(time) {} 

void Neuron::update ( int increment) {
	double temps(SimulationStart+increment*h); //variable locale pour optimiser les calculs
	if (!isRefractory(temps)) { // si le neurones est en periode refractaire, il est insensible aux stimuli
		double cst(exp(-increment*h/tau)); // variable locale pour optimiser 
		potential = cst*potential + I*R*(1-cst); // m-a-j de la valeur du potentiel
		if (potential >= threshold) { 
			++spikeNumber; 
			timeSpike = temps;
			storePotential();
			potential = Vr; //pot revient a sa valeur seuil
			}
		}
	}

bool Neuron::isRefractory( double atTime) const { // si le temps depuis le dernier spike est < au temps de pause refractaire
	return (getTimeSpike()+tau_rp <= atTime);
	}
