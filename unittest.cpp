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

TEST(OneNeurones, ResetPotential)  {
	Excitatory n1 (1.01);
	
	// time_spike le temps auquel le neurone 1 va spiker (chez moi a 923 pour ces parametres)
	for (int i(0); i < 923 +D; ++i) {
		if (n1.update()) {
			EXPECT_EQ(0.0, n1.getPotential());
			}} }

TEST(OneNeuron, FirstSpikeTime) { // fonctionnel
	Excitatory n(1.01);
	for (int i(0); i <= 922; ++i ) {
		n.update();}
	EXPECT_EQ(0, n.getSpikeNumber());
	n.update();
	EXPECT_EQ(1, n.getSpikeNumber());
	EXPECT_EQ(0.0, n.getPotential());
	}
	
	/*
TEST(TwoNeurones, SpikeTransmission)  {
	Excitatory n1 (1.01);
	Excitatory n2(0, D) ; //delay as defined in the cst file
	// time_spike le temps auquel le neurone 1 va spiker (chez moi a 923 pour ces parametres)
	for (int i(0); i < 923 +D; ++i) {
		if (n1.update()) {
			n2.writeinBuffer(i+D);
			}
		} 
	n2.update(); // logiquement on va lire la case contenant le potentiel transmis par n1.
	EXPECT_EQ(Je, n2.getPotential());
	}


*/
int main (int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}






