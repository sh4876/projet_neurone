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
        Inhibitory(double I_ext= I ); //!< constructor	
        ~Inhibitory() override; //!< destructor
        void writeinBuffer(const int& time ) override; //!< writes in its ring buffer the inputs received from spiking neurons it's connected to

        };

#endif
