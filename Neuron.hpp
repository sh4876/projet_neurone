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
	 
	int Delay_;
	double I_ext_;
	double potential_;
	int spikeNumber_;
	int timeSpike_;
	int local_clock_;
	Buffer buffer_;
	
	bool isRefractory(const int&) const; //dit si le neurone est en periode refractaire a un temps donné
	void storePotential (ofstream& out ) const; 
	
	public :
	
	Neuron(  double I_ext= I , int Delay=STEP_D, double potential=Vr, int spikeNumber=0, int timeSpike=-tau_rp, int local_clock=0); // initialisation$
	~Neuron();
	double getPotential() const;
	int getSpikeNumber() const;
	int getTimeSpike() const;
	void writeinBuffer(const int& time );
	void set_Iext(double) ;
	
	bool update () ; 
	
};
	

 
#endif
