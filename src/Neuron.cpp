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

Neuron::Neuron(double Iexterne, double Delay, double potential, int local_clock ) : I_ext_(Iexterne), 
potential_(potential)

{	///admit initialisation is in ms
	
	timeSpike_=0; // //permet de spiker des le temps zero (voir pour cela la fonction isRefractory)
	spikeNumber_= 0;
	Delay_=Delay/h;
	local_clock_=local_clock/h;
	
	for (size_t i(0); i < Buffersize; ++i) {buffer_.push_back(0.0);}
	
	
} 
Neuron::~Neuron(){}

bool Neuron::update ( ) {
	// cout << "peut spiker a partir de : " << getTimeSpike()+STEP_tau_rp << endl; 
	if (!isRefractory(local_clock_)) { // si le neurone est en periode refractaire, il est insensible aux stimuli

		cout << "local clock " << local_clock_<< endl;
		 cout << "INDEX DU BUFFER LU "<< (local_clock_)%(Delay_+1) << endl; 
		
		potential_ = C1*potential_ + I_ext_*C2 + buffer_[(local_clock_)%(Delay_+1)]; // m-a-j de la valeur du potentiel
		
		buffer_[(local_clock_)%(Delay_+1)] = 0; //vide la case correspondante du buffer 
			
		cout << "potentiel " << potential_ <<endl;
		if (potential_ >= threshold) { 
			//cout << "test" << potential_ << endl;
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
			cout << "Neurone refractaire " << endl; }
		++local_clock_;
			return false;
	}

bool Neuron::isRefractory(const int& time) const { // si le temps depuis le dernier spike est < au temps de pause refractaire
	if (getSpikeNumber() <= 0 )  {
		return false;	}
		
	else { //cout << "getTimeSpike(): " << getTimeSpike()  << endl; 
		return (getTimeSpike()+STEP_tau_rp > time);}
	
	}


void Neuron::set_Iext(double Iext) {
	I_ext_ = Iext; 
	} 

