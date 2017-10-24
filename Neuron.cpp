#include "Neuron.hpp"
#include <iostream>


void Neuron::storePotential (ofstream & out) const {
	out << getTimeSpike()*h << " " << getPotential() << endl;}
	
double Neuron::getPotential() const {
	return potential_;}

int Neuron::getSpikeNumber() const {
	return spikeNumber_;}
	
int Neuron::getTimeSpike() const {
	return timeSpike_;}

Neuron::Neuron(double Iexterne, int Delay, double potential, int spikeNumber, int timeSpike, int local_clock ) : I_ext_(Iexterne), 
potential_(potential), spikeNumber_(spikeNumber)

{	///admit initialisation is in ms
	timeSpike_=timeSpike/h;
	Delay_=Delay/h;
	local_clock_=local_clock/h;
	
	for (size_t i(0); i < Buffersize; ++i) {buffer_.push_back(0.0);}
	
	
} 
Neuron::~Neuron(){}

bool Neuron::update ( ) {
	if (!isRefractory(local_clock_)) { // si le neurone est en periode refractaire, il est insensible aux stimuli
		cout << " calcul du potentiel" << flush;
		int indexdubuffer((local_clock_)%Delay_);
		cout << "indexdu buffer " << indexdubuffer << endl;
		potential_ = C1*potential_ + I_ext_*C2 + buffer_[(local_clock_)%Delay_]; // m-a-j de la valeur du potentiel
		cout <<"vider de la case du buffer lue " << flush;
			buffer_[(local_clock_)%Delay_] = 0; //vide la case correspondante du buffer 
			
		
		cout << "potentiel " << potential_ << threshold<<endl;
		if (potential_ >= threshold) { 
			cout << "test" << potential_ << endl;
			++spikeNumber_; 
			cout << "nombre de spike " << getSpikeNumber() << endl; 
			cout << "heure locale " << local_clock_ << endl; 
			timeSpike_ = local_clock_;
			ofstream PotentialStorageFile("potentials.txt");
			storePotential(PotentialStorageFile);
			potential_ = Vr; //pot revient a sa valeur seuil
			return true;
			}
		
		} else { 
			cout << "Neurone refractaire " << endl;}
			++local_clock_;
			cout << "fin du update dans neurone"<< endl;
			return false;
	}

bool Neuron::isRefractory(const int& time) const { // si le temps depuis le dernier spike est < au temps de pause refractaire
	
	cout <<"time" << time << endl; 
	return (getTimeSpike()+STEP_tau_rp > time);
	}

void Neuron::writeinBuffer(const int& time){	
	size_t index (0);
	index = (time + buffer_.size()-1)%buffer_.size();
	buffer_[index] += J;
	}

void Neuron::set_Iext(double Iext) {
	I_ext_ = Iext; 
	} 


