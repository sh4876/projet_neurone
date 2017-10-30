#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "Constants.hpp"

using namespace std;

//{}



typedef vector<double> Buffer;

class Neuron {
	
	private :
	
	double I_ext_; 					//!< external current 
	int Delay_;
	double potential_;				//!< membrane potential
	int spikeNumber_;				//!< number of spike since simulation start
	int timeSpike_;					//!< time of last spike
	int local_clock_;				//!< neuron's local clock
	
	
	bool isRefractory(const int&) const; //dit si le neurone est en periode refractaire a un temps donné
	void storePotential (ofstream& out ) const; 
	
	protected : 
	Buffer buffer_;
	
	public :
	
	
	Neuron(  double I_ext, double Delay, double potential, int local_clock); //!< constructor
	virtual ~Neuron();	//!<  destructor
	double getPotential() const; //!<  gets the potential of the membrane
	int getSpikeNumber() const;	//!<  gets the number of spike since simulation start
	int getTimeSpike() const;	//!<  gets time of last spike
	virtual void writeinBuffer(const int& time ) =0  ; //!< neuron spiking at time (localclock ) sends a signal to every neuron it s connected to
	void set_Iext(double) ;	//!< setter of external current
	
	bool update () ; //!< updates the neuron of one step
	
};

 
#endif
