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

Neuron::Neuron(double pot=Vr, int spike=0, double timeofSpike=0.0, double timeofSimulation= SimulationStart ) : potential(pot), spikeNumber(spike), 
timeSpike(timeofSpike), local_clock(timeofSimulation) {} 

void Neuron::update ( ) {
	if (!isRefractory(local_clock)) { // si le neurones est en periode refractaire, il est insensible aux stimuli
		double cst(exp(-h/tau)); // variable locale pour optimiser 
		potential = cst*potential + I*R*(1-cst); // m-a-j de la valeur du potentiel
		cout << "potentiel " << potential << threshold<<endl;
		if (potential >= threshold) { 
			cout << "test" << potential << endl;
			++spikeNumber; 
			timeSpike = local_clock;
			storePotential();
			potential = Vr; //pot revient a sa valeur seuil
			++local_clock;
			}
		} else { cout << "Neurone refractaire " << endl;}
	}

bool Neuron::isRefractory( double atTime) const { // si le temps depuis le dernier spike est < au temps de pause refractaire
	return (getTimeSpike()+tau_rp <= atTime);
	}
