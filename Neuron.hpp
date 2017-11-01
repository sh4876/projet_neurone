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

        double I_ext_;                                  //!< external current
        double potential_;                              //!< membrane potential
        int spikeNumber_;                               //!< number of spike since simulation start
        int timeSpike_;                                 //!< time of last spike
        int local_clock_;                               //!< neuron's local clock
		bool external_noise_;


        bool isRefractory(const int&) const; //!< State of neuron (refractory or not)
        void storePotential (ofstream& out ) const;

        protected :
		Buffer buffer_; 	//!< saves inputs of spiking neuron of wich "this" is a target

        public :


        Neuron(  double I_ext); //!< constructor
        virtual ~Neuron();      //!<  destructor
        double getPotential() const; //!<  gets the potential of the membrane
        int getSpikeNumber() const;     //!<  gets the number of spike since simulation start
        int getTimeSpike() const;       //!<  gets time of last spike
        virtual void writeinBuffer(const int& time ) =0  ; //!< neuron spiking at time (localclock ) sends a signal to every neuron it s connected to
        void set_Iext(double) ; //!< setter of external current
		vector <Neuron*> targets;
        bool update () ; //!< updates the neuron of one step
		void setExternalNoise(bool YesOrNo);
};


#endif
