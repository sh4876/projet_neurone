#ifndef EXCITATORY_HPP
#define EXCITATORY_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "Constants.hpp"
#include "Neuron.hpp"

using namespace std;

class Excitatory : public Neuron {
	
	public :
 	Excitatory(double I_ext= I , double Delay=D, double potential=Vr, int local_clock=0);
    ~Excitatory() override ;
    
    ///write in ring buffer.
    /**
     * erer
     * @param hallo
     * @see hallo
     * @return double
     */
  	void writeinBuffer(const int& time ) override ;
	
	};



#endif
