#include "Simulation.hpp"

#include "Neuron.hpp"

#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include <random>

using namespace std;

//{}
// []

/**Constructor
 * @param total Number of neurone (NB_Neurones as default value)
 */
Simulation::Simulation(unsigned int weight_connection_ratio, unsigned int Eta, unsigned int NbNeurons, unsigned int EndSimulation, double ExternalCurrent):
	 weight_connection_ratio_(weight_connection_ratio), Eta_(Eta), NbNeurons_(NbNeurons), EndSimulation_(EndSimulation/h) , ExternalCurrent_(ExternalCurrent)
{
	NbExcitatory_ = NbNeurons_*(1-NEURON_RATIO);
	NbInhibitory_ = NbNeurons_*NEURON_RATIO;
	
	Ce_ = NbExcitatory_*CONNECTION_RATIO; //!< CONNECTIONS_FROM_EXCITATORY
	Ci_ = NbInhibitory_*CONNECTION_RATIO; //!< CONNECTIONS_FROM_INHIBITORY
	
    CreateExcitatory();
    CreateInhibitory();
}


 /**RunSimulation
  * makes the connections between the neurones of the network
  * updates until the end of the simulation
  * @see main
  */
void Simulation::RunSimulation() {
		ConnectNetwork();
		UpdateSimulation();
		for (auto n : Neurone) {
			cout << n->getNumTarget() << endl;
		
		}

}

/**UpdateSimulation
 * check if the table of neurone is not empty
 * updates every neuron
 * if a neuron has a spike, an input is written in the buffer of it's targets
 * time of simulation incremented once each neuron has been updated once
 * @param step time at wich the simulation must end
 * @see RunSimulation
 */
void Simulation::UpdateSimulation () {
	int nbspikes (0);
	
    if (!Neurone.empty()) {
        unsigned int globalClock(0);
        while (globalClock < EndSimulation_) {

            for( size_t i(0); i<Neurone.size(); ++i) {
                if (Neurone[i] == nullptr) {cout << "pointeur nul" << endl;}

                ///update du neurone dans tous les cas
                else if (Neurone[i]->update() ) {
					++nbspikes;
                    int atStepTime(Neurone[i]->getTimeSpike().back());
                    for (auto& target : Neurone[i]->getTargets()) {
                        target-> writeinBuffer(atStepTime);
                    }
                }
            }
        ++globalClock;
        }
    }      
}


/**CreateConnection
 * neuron of index2 becomes a target of neuron of index1
 * @param indexes of two neurones in the table
 * @see ConnectNetwork
 */
void Simulation::CreateConnection(const size_t& index1, const size_t& index2) {
    assert(index1<Neurone.size());
    assert(index2<Neurone.size());
    if (index1 != index2) {
    Neurone[index1]->addTarget(Neurone[index2]);
    
    }
 }

/**ConnectNetwork
 * generates the random connection between the neurons of the table
 * @see RunSimulation
 */
 void Simulation::ConnectNetwork() {
         default_random_engine sv;
         mt19937 random_list (sv());
         uniform_int_distribution<int> excitatory(0, NbExcitatory_-1);
         uniform_int_distribution<int> inhibitory(NbExcitatory_, NbNeurons_-1);
         for (size_t target(0); target < NbNeurons_; ++target) {

                for (size_t i(0); i < Ce_; ++i) {
                       // auto source(excitatory(random_list));
                        CreateConnection(excitatory(random_list),target);
                        //cerr<<"DEBUG: creation connection" << i << " " << excitatory(random_list)<<endl;
                        
                 }
                for (size_t i(0); i < Ci_; ++i) {
                        //auto source(inhibitory(random_list));
                        CreateConnection(inhibitory(random_list), target);
                }
        }
        
}


/**CreateExcitatory
 * generates a certain amount of excitatory neurones with external current
 * @param number of excitatory numbers whished, value of the external current (default value is I given in the constants file)
 * @see constructor
 */
void Simulation::CreateExcitatory () {
    for (unsigned int i(0); i < NbExcitatory_ ; ++i) {
        Neurone.push_back(new Neuron(false, ExternalCurrent_, Eta_, weight_connection_ratio_ ));
    }
}

/**CreateInhibitory
 * generates a certain amount of inhibitory neurones
 * @param number of inhibitory neurones whished, value of the external current (default value is I given in the constants file)
 * @see constructor
 */
void Simulation::CreateInhibitory () {
    for (unsigned int i(0); i < NbInhibitory_ ; ++i) {
        Neurone.push_back(new Neuron(true,  ExternalCurrent_ , Eta_, weight_connection_ratio_ ));
    }
}

                ///methods used in unittests

/**Connected
 * @param indexes of two neurones in the table
 * @see used in unittests
 * @return if neuron of index2 is a target of neuron of index1
 */
bool Simulation::Connected (const size_t& index1, const size_t& index2) const {
	assert(index1<Neurone.size());
    assert(index2<Neurone.size());
    for (const auto& target : Neurone[index1]->getTargets() ) {
        if (target == Neurone[index2]) {return true;}
    }
    return false;
}

/**get_NbNeurones
 * @see used in unittests
 * @return number of neurones in the table
 */
unsigned int Simulation::get_NbNeurones () const {
    return Neurone.size();}

/**getNeuronePotential
 * @param index of the neurone of which we want to know the potential
 * @see used in unittests
 * @return potential of given neuron
 */
double Simulation::getNeuronePotential (size_t index) const {
    return Neurone[index]->getPotential(); }

//{}

void Simulation::writeSpikeInFile( const string& file) {
	ofstream out(file);
	if (out.fail()) {


		cerr << "impossible to write in file" << file << flush;
	} else {
		
		for ( size_t i(0); i< Neurone.size(); ++i) {
			assert((Neurone[i]-> getTimeSpike()).size() > 0 );
			cout << (Neurone[i]-> getTimeSpike()).size() << endl; 
			for ( const auto& spike : Neurone[i]->getTimeSpike()) {
				out << spike*h << '\t' << i << '\n'; 
			}
		}
	}
	out.close();
}

void Simulation::shutExternalNoise() {	
	for ( auto& n : Neurone ) 
		{n->setExternalNoise( false);
	}
}
