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
        int spikeNumber_;                               //!< number of spike since simulation start
        vector<double > timeSpike_;                                 //!< time of last spike
        int local_clock_;                               //!< neuron's local clock
		bool external_noise_;							//!< true if we allowed the neuron to get random inputs from the rest of the brain 
											
		double V_ext_;								//!< external firing rate
        bool isRefractory(const int&) const;		//!< State of neuron (refractory or not)
       
		Buffer buffer_; 							//!< saves inputs of spiking neuron of wich "this" is a target
		vector <Neuron*> targets; 		//!< neurones that get an input in their buffer when the neurones spikes 
		double noise () const ;
	
        public :

        Neuron( bool Inhib,  double I_ext= 0, int Eta=ETA, int weight_connection_ratio = WEIGHT_CONNECTION_RATIO); //!< constructor
        ~Neuron();      				//!<  destructor
        
        
        double getPotential() const; 	//!<  gets the potential of the membrane
        int getSpikeNumber() const;     //!<  gets the number of spike since simulation start
        vector <double> getTimeSpike() const;       //!<  gets time of last spike
        
        bool update () ; 						//!< updates the neuron of one step
        void writeinBuffer(const int& time )  ; //!< neuron spiking at time (localclock ) sends a signal to every neuron it s connected to
        void set_Iext(double) ; 				//!< setter of external current
		
		void setExternalNoise(bool YesOrNo); //!< set to true if we allow the neuron to get random inputs from the rest of the brain 
		void addTarget ( Neuron* n);
		size_t getNumTarget () const ; 
		vector<Neuron*> getTargets() ;
};


#endif
