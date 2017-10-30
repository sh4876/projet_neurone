#include "Inhibitory.hpp"
#include "Neuron.hpp"

#include <iostream>

Inhibitory::Inhibitory(double Iexterne, double Delay, double potential, int local_clock) : 
	Neuron(Iexterne,Delay,potential,local_clock) {}
 


void Inhibitory::writeinBuffer(const int& time){	
	size_t index (0);
	index = (time + buffer_.size()-1)%buffer_.size(); 
	buffer_[index] -= Ji;
	}

Inhibitory::~Inhibitory(){}
