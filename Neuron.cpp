#include "Neuron.hpp"
#include <iostream>
#include <random>

/**Constructor
 * @param external current wich has I(defined in the constants) as default value
 * initialise all the cases of the buffer with the value of zero
 */
Neuron::Neuron(double Iexterne ) : I_ext_(Iexterne)

{       ///admit initialisation is in ms
		potential_ = 0.0;
        timeSpike_=0; // //permet de spiker des le temps zero (voir pour cela la fonction isRefractory)
        spikeNumber_= 0;
        local_clock_=0;
		external_noise_=false;
        for (size_t i(0); i < Buffersize; ++i) {buffer_.push_back(0.0);}


}
Neuron::~Neuron(){}


/**storePotential
 * @param external stream
 * @see in update if spike occurs
 */
void Neuron::storePotential (ofstream & out) const {
        out << getTimeSpike()*h << " " << getPotential() << endl;}

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
int Neuron::getTimeSpike() const {
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

        double noisyPotential(0);
        if (external_noise_) {
            random_device rd;
            mt19937 randomList(rd());
            poisson_distribution<> pois(V_ext_step);
            noisyPotential = pois(randomList);
            }

        cout << "local clock " << local_clock_<< endl;
        potential_ = C1*potential_ + I_ext_*C2 + buffer_[(local_clock_)%(Buffersize)] + noisyPotential  ; // m-a-j de la valeur du potentiel

        buffer_[(local_clock_)%(Buffersize)] = 0; //vide la case correspondante du buffer

        cout << "potentiel " << potential_ <<endl;
        if (potential_ >= threshold) {
            ++spikeNumber_;
            cout << "nombre de spike " << getSpikeNumber() << endl;
            cout << "heure locale " << local_clock_ << endl;
            timeSpike_ = local_clock_;
            ofstream PotentialStorageFile("potentials.txt");
            storePotential(PotentialStorageFile);
            potential_ = Vr; //pot revient a sa valeur seuil
            return true;
            }

        } else {
            cout << "Neurone refractaire " << endl; }
        ++local_clock_;
            return false;
    }

/**isRefractory
 * if the delay since the last spike hasnt expired the neuron cant update its potential
 * @param given time (corresponding to localclock)
 * @see update
 * @return if neurone is indeed refractory
 */
bool Neuron::isRefractory(const int& time) const { // si le temps depuis le dernier spike est < au temps de pause refractaire
        if (getSpikeNumber() <= 0 )  {
                return false;   }

        else { //cout << "getTimeSpike(): " << getTimeSpike()  << endl;
                return (getTimeSpike()+STEP_tau_rp > time);}

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
