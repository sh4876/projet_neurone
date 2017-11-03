#include "Neuron.hpp"
#include <iostream>
#include <random>

#include "Constants.hpp"

/**Constructor
 * @param Nature of the neurone (inhibitoty or excitatory), external current, 
 * external firing rate over rate to reach threshold, weight of inhibitory input over excitatory
 * 
 * external noise is set to true as default but can be change by a setter (usefull in unittests)
 * initialise all the cases of the buffer with the value of zero
 */
Neuron::Neuron(bool Inhib , double Iexterne , int Eta , int weight_connection_ratio) : isInhibitory_(Inhib ), I_ext_(Iexterne), Eta_(Eta) , 
weight_connection_ratio_ (weight_connection_ratio) 

{     
		potential_ = 0.0;
        spikeNumber_= 0;
        local_clock_=0;
		external_noise_=true;
		V_ext_ =Eta* threshold/(Je*tau)*h;
        for (size_t i(0); i < Buffersize; ++i) {buffer_.push_back(0.0);}
}

Neuron::~Neuron(){}

/**getPotential
 * @see in method storePotential and in unitests
 * @return value of the potential
 */
double Neuron::getPotential() const {
        return potential_;}

/**getSpikeNumber
 * @see in method storePotential, in method isRefractory and in unitests
 * @return number of spike since simulationstarted
 */
int Neuron::getSpikeNumber() const {
        return spikeNumber_;}

/**getTimeSpike
 * @see in method storePotential, in method isRefractory
 * @return time of last spike
 */
vector <double> Neuron::getTimeSpike() const {
        return timeSpike_;}


/**update of one steptime
 * if the neurone isn t refractory, it will update its potential.
 * if we allow the neurone to receive background noise from the rest of
 * the brain, then an additionnal potential must be taken into account.
 * if the neuron has a spike, it writes the time and the value of the
 * spike in an external file.
 * incrementation of the local clock at the end of update.
 * @see in Simulation.update
 * @return true if neuron had a spike
 */
bool Neuron::update ( ) {
       if (!isRefractory(local_clock_)) {

 
        potential_ = C1*potential_ + I_ext_*C2 + buffer_[(local_clock_)%(Buffersize)] + noise()  ; // m-a-j de la valeur du potentiel

        if (potential_ >= threshold) {
            ++spikeNumber_;
         
            timeSpike_.push_back(local_clock_/h);
            potential_ = Vr; //pot revient a sa valeur seuil
            return true;
            }

        } else {
          
            }
        buffer_[(local_clock_)%(Buffersize)] = 0; //vide la case correspondante du buffer
        ++local_clock_;
            return false;
}

double Neuron::noise () const {
	double noisyPotential(0);
       if (external_noise_) { 
            static random_device rd;
            static mt19937 generator(rd());
            static poisson_distribution<int> pois(V_ext_);
            noisyPotential = Je*pois(generator);
            }
    return noisyPotential; 
	
	}
/**writeinBuffer
 * ADDS an current at a certain index in the ring buffer for it to be
 * added to the potential latter in the simulation
 * @param time at wich the neuron sending the input had a spike
 * @see in update
 */
void Neuron::writeinBuffer(const int& time){
        size_t index (0);
        index = (time + buffer_.size()-1)%buffer_.size();
        if (isInhibitory_) {buffer_[index] -= Je*WEIGHT_CONNECTION_RATIO;
			} else {buffer_[index] += Je; }
}


/**isRefractory
 * if the delay since the last spike hasnt expired the neuron cant update its potential
 * @param given time (corresponding to localclock)
 * @see update
 * @return if neurone is indeed refractory
 */
bool Neuron::isRefractory(const int& time) const { // si le temps depuis le dernier spike est < au temps de pause refractaire
        if (getSpikeNumber() < 1 )  {
			return false;   
		}else { 
			return (timeSpike_.back()+STEP_tau_rp > time);
		}
}

/**set_Iext
 * @param external current
 * @see used in unittests
 */
void Neuron::set_Iext(double Iext) {
        I_ext_ = Iext;
        }

/**setExternalNoise
 * @param true if we want the neuron to receive random inputs from rest of the brain
 * @see used in unitests (to have predictable results)
 */
void Neuron::setExternalNoise(bool YesOrNo) {
     external_noise_= YesOrNo;
}

void Neuron::addTarget (Neuron* n){
	targets.push_back(n);
}	

size_t Neuron::getNumTarget () const {
	
	return targets.size();
	}
	
vector<Neuron*> Neuron::getTargets() 
{
	return targets;
}
