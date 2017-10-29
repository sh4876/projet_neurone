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
	
	double I_ext_;
	int Delay_;
	double potential_;
	int spikeNumber_;
	int timeSpike_;
	int local_clock_;
	
	
	bool isRefractory(const int&) const; //dit si le neurone est en periode refractaire a un temps donné
	void storePotential (ofstream& out ) const; 
	
	protected : 
	Buffer buffer_;
	
	public :
	
	
	Neuron(  double I_ext, double Delay, double potential, int local_clock); // initialisation$
	virtual ~Neuron();
	double getPotential() const;
	int getSpikeNumber() const;
	int getTimeSpike() const;
	virtual void writeinBuffer(const int& time ) =0  ; 
	void set_Iext(double) ;
	
	bool update () ; 
	
};

 
#endif
