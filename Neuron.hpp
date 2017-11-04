#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "Constants.hpp"
#include <random>

using namespace std;

//{}

typedef vector<double> Buffer;



class Neuron {

        private :
		
	bool isInhibitory_;								//!< true if the neurone is inhibitory, false if excitatory
	double I_ext_;                                  //!< external current
	int Eta_;										//!<  external firing rate over rate to reach threshold
	int weight_connection_ratio_;					//!< inhibitory over excitatory;
	
	double potential_;                              //!< membrane potential
	vector<double > timeSpike_;                                 //!< time of last spike
	int local_clock_;                               //!< neuron's local clock
	bool external_noise_;							//!< true if we allowed the neuron to get random inputs from the rest of the brain 
											
	double V_ext_;									//!< external firing rate
	bool isRefractory(const int&) const;			//!< State of neuron (refractory or not)
       
	Buffer buffer_; 								//!< saves inputs of spiking neuron of wich "this" is a target
	vector <Neuron*> targets; 						//!< neurones that get an input in their buffer when the neurones spikes 
	double noise () const ;							//!< calculates the background noise using poisson distribution
	
        public :

	Neuron( bool Inhib,  double I_ext= 0, int Eta=ETA, int weight_connection_ratio = WEIGHT_CONNECTION_RATIO); //!< constructor
	~Neuron();      								//!<  destructor
             
	bool update () ; 								//!< updates the neuron of one step
	void writeinBuffer(const int& time )  ; 		//!< neuron spiking at time (localclock ) sends a signal to every neuron it s connected to
	void addTarget ( Neuron* n); 					//!< adds a target to wich the neuron will send current if it s spiking
	
	void set_Iext(const double&) ; 					//!< setter of external current	
	void setExternalNoise(const bool& YesOrNo); 	//!< set to true if we allow the neuron to get random inputs from the rest of the brain 
	
	double getPotential() const; 					//!<  gets the potential of the membrane
	vector <double> getTimeSpike() const;       	//!<  saves the time of the spikes 
	vector<Neuron*> getTargets() const;				//!< return the vector containing pointers to all the neurons it should send current to in case of spike
};


#endif
