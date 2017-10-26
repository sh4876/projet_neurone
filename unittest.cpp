#include <iostream>
#include <cmath>
#include <gtest/gtest.h>
#include "Neuron.hpp" 
#include "Excitatory.hpp"
#include "Inhibitory.hpp"
#include "Simulation.hpp"
//{}
//TEST () {}


TEST(OneNeurone, OneUpdate) {
	Excitatory neuron;
	neuron.set_Iext(1.0);
	neuron.update();
	EXPECT_EQ(1.0*20*(1-exp(-0.1/20)), neuron.getPotential());
}

TEST(OneNeurone, TwoUpdates) {
	Excitatory neuron;
	neuron.set_Iext(1.0);
	neuron.update();
	neuron.update();

	double pot1 (1.0*20*(1-exp(-0.1/20)));
	double valeur_attendue(pot1*exp(-0.1/20) + 1.0*20*(1-exp(-0.1/20)));
	EXPECT_EQ(valeur_attendue, neuron.getPotential());
}

TEST(SimulationwithTwoNeurones, numberOfNeurones){
	Simulation sim(2);
	unsigned int a(2);
	EXPECT_EQ(a, sim.get_NbNeurones());
}

TEST(SimulationwithTwoNeurones, ConnectionToAnother) {

	Simulation sim(2);
	sim.CreateConnection(0,1);
	EXPECT_TRUE(sim.Connected(0,1));
}

TEST(SimulationwithTwoNeurones, ConnectionToItself) {
	Simulation sim(2);
	sim.CreateConnection(0,0);
	EXPECT_FALSE(sim.Connected(0,0));
}

int main (int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}






