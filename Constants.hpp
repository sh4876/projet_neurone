#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP


#include <iostream>
#include <cmath>
using namespace std;

const int NB_NEURONES(1);
const int I(1); // l intensite du courant 
const double h(0.1); // intervalle de temps en millisecondes
const double SimulationStart(0);
const double SimulationStop(400);
const double tau(20); // membrane time constant of an excitatory neurone in ms
const double Vr(0.0); // reset potential in mV
const double tau_rp(20); //refractory period in ms
const double threshold(20); // threshold potential in mV
const double R(20); // la resistance en GOhm
const double J(0.1); // the EPSP amplitude in ms
const double D(1.5); // the delay in ms

const double C1(exp(-h/tau));
const double C2(R*(1-C1));

/// conversion en pas de temps; 
const int STEP_SimulationStart=(int)SimulationStart/h;
const int STEP_SimulationStop=(int)SimulationStop/h;
const int STEP_tau=(int)tau/h;
const int STEP_tau_rp=(int)tau_rp/h;
const int STEP_D=(int)D/h;

const int Buffersize(STEP_D+1); 

const string Path= "potentials.txt";

#endif

/* const int NB_Neurones(8);
 * const double NEURONE_RATIO(0.25); //   Inhibitory over Excitatory
 * 
 * const int NB_Excitatory(NB_Neurones*(1-NEURONE_RATIO));
 * const int NB_Inhibitory(NB_NEURONE*NEURONE_RATIO);
 * 
 * const double CONNECTION_RATIO(0.01);
 * const int Ce(NB_Excitatory*CONNECTION_RATIO); //CONNECTIONS_FROM_EXCITATORY
 * const int Ci(NB_Inhibitory*CONNECTION_RATIO); //CONNECTIONS_FROM_INHIBITORY
 * const int C_ext(Ce); //EXTERNAL_CONNECTIONS
 * 
 * const int WEIGHT_CONNECTION_RATIO(5); //inhibitory over excitatory;
 * const double Je(0.1); //transmitted value of excitatory spike (weight)
 * const double Ji(Je*WEIGHT_CONNECTION_RATIO);  //transmitted value of inhibitory spike (weight)
 * //assert Je et Ji < threshold
 * 
 * const double mu_thr(threshold/ (Ce*Je*tau));
 * const double mu_ext(2*mu_thr); //firing rate for external neuron
 * 
 * */
