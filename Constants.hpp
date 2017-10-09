#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

const int nbNeurones(1);
const int I(2); // l intensite du courant 
const double h(20); // intervalle de temps en millisecondes
const double SimulationStart(0);
const double SimulationStop(400);
const double tau(20); // membrane time constant of an excitatory neurone in ms
const double Vr(0.0); // reset potential in mV
const double tau_rp(30); //refractory period in ms
const double threshold(20); // threshold potential in mV
const double R(tau/nbNeurones); // la resistance
 


#endif
