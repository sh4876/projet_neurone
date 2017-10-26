#ifndef INHIBITORY_HPP
#define INHIBITORY_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "Constants.hpp"
#include "Neuron.hpp"

using namespace std;

class Inhibitory : public Neuron {
	
	public :
	Inhibitory(double I_ext= I , double Delay=D, double potential=Vr,  int local_clock=0);
	~Inhibitory() override;
	void writeinBuffer(const int& time ) override;
	
	};

#endif
