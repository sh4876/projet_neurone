#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "Constants.hpp"
#include <string>

using namespace std;

class Neuron; 


class Simulation {

        private:

unsigned int weight_connection_ratio_;			//!< inhibitory over excitatory;
unsigned int Eta_;								//!<  external firing rate over rate to reach threshold

unsigned int NbNeurons_; 						//!< total number of neurons 
unsigned int NbExcitatory_;						//!< total number of excitatory neurons 
unsigned int NbInhibitory_;						//!< total number of inhibitory neurons 

unsigned int EndSimulation_; 					//!< time of simulation end in ms
double ExternalCurrent_;						//!< external current given to the neurons in mA

unsigned int Ce_;
unsigned int Ci_;

vector<Neuron*> Neurone;                //!< saves all the neuron involved in the simulation

void CreateExcitatory () ;				//!< creates all excitatory neurons 
void CreateInhibitory () ;				//!< creates all excitatory neurons


        public :
Simulation(unsigned int weight_connection_ratio, unsigned int Eta_, unsigned int NbNeurons = NB_NEURONS,  
	unsigned int EndSimulation= END_SIMULATION, double ExternalCurrent=0.0 );          //!< constuctor
void RunSimulation();                           //!< runs the simulation
void UpdateSimulation ();       				//!< updates simulation from globalClock until Endsimulation is reached 
void CreateConnection(const size_t& index1, const size_t& index2); //!< creates connections between two neurones
void ConnectNetwork() ; 						//!< randomly connects the whole network
bool Connected (const size_t& index1, const size_t& index2) const; //unecessary
unsigned int get_NbNeurones () const ; 			//!< return number of neuron in the simulation
double getNeuronePotential(size_t index) const; //utile pour les tests
void writeSpikeInFile( const string& file);
void shutExternalNoise(); 
        };

#endif
