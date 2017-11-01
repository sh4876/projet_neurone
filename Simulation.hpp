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
unsigned int NbNeurons_;
unsigned int NbExcitatory_;
unsigned int NbInhibitory_;

unsigned int Ce_;
unsigned int Ci_;

vector<Neuron*> Neurone;                //!< saves all the neuron involved in the simulation

int EndSimulation_; 
double ExternalCurrent_;
int weight_connection_ratio_;					//!< inhibitory over excitatory;
int Eta_;										//!<  external firing rate over rate to reach threshold

void CreateExcitatory () ;
void CreateInhibitory () ;


        public :
Simulation(int weight_connection_ratio, int Eta_, unsigned int NbNeurons = NB_NEURONS,  int EndSimulation= END_SIMULATION, double ExternalCurrent=0 );          //!< constuctor
void RunSimulation();                           //!< runs the simulation
void UpdateSimulation ();       //!< updates simulation from globalClock until SimulationEnd
void CreateConnection(const size_t& index1, const size_t& index2); //!< creates connections between two neurones
void ConnectNetwork() ; //!< randomly connects the whole network
bool Connected (const size_t& index1, const size_t& index2) const; //unecessary
unsigned int get_NbNeurones () const ; //!< return number of neuron in the simulation
double getNeuronePotential(size_t index) const; //utile pour les tests
void writeSpikeInFile( const string& file);
void shutExternalNoise(); 
        };



//eventuellement faire une methode qui ajoute des neurones


#endif
