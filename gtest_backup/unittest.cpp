#include <iostream>
#include <cmath>
#include "Neuron.hpp" // refaire le chemin car pas dans le meme repertoire

//{}
//TEST () {}

TEST (OneNeurone, OneUpdate) {
	Neuron neuron;
	neuron.set_I_ext(1.0);
	neuron.update();
	EXPECT_EQ(1.0*20*(1-exp(-0.1/20)), neuron.getPotential());
}

TEST (OneNeurone, TwoUpdates) {
	Neuron neuron;
	neuron.set_I_ext(1.0);
	neuron.update();
	neuron.update();

	double pot1 (1.0*20*(1-exp(-0.1/20));
	double valeur_attendue(pot1*exp(-0.1/20) + 1.0*20*(1-exp(-0.1/20));
	EXPECT_EQ(valeur_attendue, neuron.getPotential());
}

TEST (SimulationwithTwoNeurones, numberOfNeurones){
	Simulation sim(2);
	EXPECT_EQ(sim.get_NbNeurones(),2);
}

TEST (SimulationwithTwoNeurones, ConnectionToAnother) {

	Simulation sim(2);
	sim.CreateConnection(0,1);
	EXPECT_EQ(sim.Connected(0,1),true);
}

TEST (SimulationwithTwoNeurones, ConnectionToAnother) {
	Simulation sim(2);
	sim.CreateConnection(0,0);
	EXPECT_EQ(sim.Connected(0,0),false);
}






