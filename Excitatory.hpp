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
    Excitatory(double I_ext= I ); 	//!< constructor
    ~Excitatory() override ; //!< destructor

	void writeinBuffer(const int& time ) override ; //!< transmitted value of excitatory spike (weight)  // the EPSP amplitude in ms

        };



#endif
