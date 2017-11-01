#include "Inhibitory.hpp"
#include "Neuron.hpp"

#include <iostream>

/**Constructor
 * @param external current (I as default value)
 */
Inhibitory::Inhibitory(double Iexterne) : Neuron(Iexterne) {}

/**Destructor
 */
Inhibitory::~Inhibitory(){}


/**writeinBuffer
 * SUBSTRACTS an current at a certain index in the ring buffer for it to be
 * added to the potential latter in the simulation
 * @param time at wich the neuron sending the input had a spike
 * @see in update
 */
void Inhibitory::writeinBuffer(const int& time){
        size_t index (0);
        index = (time + buffer_.size()-1)%buffer_.size();
        buffer_[index] -= Ji;
        }

