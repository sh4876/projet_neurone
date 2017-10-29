#include "Excitatory.hpp"
#include "Neuron.hpp"

#include <iostream>

Excitatory::Excitatory(double Iexterne, double Delay, double potential, int local_clock) : 
	Neuron(Iexterne,Delay,potential,local_clock) {}
 
void Excitatory::writeinBuffer(const int& time){	
	size_t index (0);
	//index = (time + buffer_.size()-1)%buffer_.size();
	index = ((time )%buffer_.size()) -1 ;
	buffer_[index] += Je;
	cout << "ajout de Je au buffer contient : " << buffer_[index] << endl;
	cout << "index du buffer" << index << endl; 
	}

Excitatory::~Excitatory(){}
