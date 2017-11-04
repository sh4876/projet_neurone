#include <iostream>
#include <cmath>
#include <gtest/gtest.h>
#include "Neuron.hpp"

#include "Simulation.hpp"
 //{}
//TEST () {}

TEST(OneNeurone, OneUpdate) {
    Neuron neuron(false);
    neuron.set_Iext(1.0);
    neuron.setExternalNoise(false);
    neuron.update();
    EXPECT_EQ(1.0*20*(1-exp(-0.1/20)), neuron.getPotential());
 }

TEST(OneNeurone, Nocurrent) {
	Neuron neuron(false);
	neuron.set_Iext(0.0);
	neuron.setExternalNoise(false);
	neuron.update();
    neuron.update();
    neuron.update();
    EXPECT_EQ(0, neuron.getPotential());
}

TEST(OneNeurone, TwoUpdates) {
    Neuron neuron(false);
    neuron.set_Iext(1.0);
    neuron.setExternalNoise(false);
    neuron.update();
    neuron.update();

    double pot1 (1.0*20*(1-exp(-0.1/20)));
    double valeur_attendue(pot1*exp(-0.1/20) + 1.0*20*(1-exp(-0.1/20)));
    EXPECT_EQ(valeur_attendue, neuron.getPotential());
}

TEST(SimulationwithTwoNeurones, numberOfNeurones){
    Simulation sim(5,2,10);
    unsigned int a(10);
    EXPECT_EQ(a, sim.get_NbNeurones());
}

TEST(SimulationwithTwoNeurones, ConnectionToAnother) {

    Simulation sim(5,2,10);
    sim.CreateConnection(0,1);
    EXPECT_TRUE(sim.Connected(0,1));
    
    sim.CreateConnection(1,0);
    EXPECT_TRUE(sim.Connected(1,0));
    
    sim.CreateConnection(2,3);
    EXPECT_TRUE(sim.Connected(2,3));
    
    sim.CreateConnection(6,7);
    EXPECT_TRUE(sim.Connected(6,7));
}

TEST(OneNeurones, ResetPotential) {
    Neuron n1 (false, 1.01);
    
    for (int i(0); i < 923 +3; ++i) {
		if (n1.update()) {
		EXPECT_EQ(0.0, n1.getPotential());
        }
    } 
}

TEST(OneNeuron, FirstSpikeTime) { 
    Neuron n(false, 1.01);
    n.setExternalNoise(false); 
    for (int i(0); i <= 922; ++i ) {
        n.update();
    }
    EXPECT_EQ(0, (n.getTimeSpike()).size());
    n.update();
    EXPECT_EQ(1, (n.getTimeSpike()).size());
	EXPECT_EQ(0.0, n.getPotential());
}


TEST(TwoNeurones, ExcitatorySpikeTransmission) {
    Neuron n1 (false, 1.01);
    Neuron n2(false, 0) ; 
    
	n1.setExternalNoise(false);
	n2.setExternalNoise(false);
    for (int i(0); i < 923 +STEP_D +1; ++i) {
		if (n1.update()) {
			n2.writeinBuffer(i);
		}
		n2.update();
	}
	EXPECT_EQ(Je, n2.getPotential());
}

TEST(TwoNeurones, InhibitorySpikeTransmission) {
    Neuron n1 (true, 1.01);
    Neuron n2(true, 0) ; 
   
	n1.setExternalNoise(false);
	n2.setExternalNoise(false);
    for (int i(0); i < 923 +STEP_D +1; ++i) {
		if (n1.update()) {
			n2.writeinBuffer(i);
		}
		n2.update();
	}
	EXPECT_EQ(-Je*WEIGHT_CONNECTION_RATIO, n2.getPotential());
}

/*TEST(SimulationwithlotsofNeurons, numberOfIncomingConnections) {
    Simulation sim(5,2,12500);
    sim.ConnectNetwork();
    unsigned int nbIncomingConnections(0);
    for (size_t i(0); i < sim.get_NbNeurones() ; ++i ) {
			if ( sim.Connected(i,1))  {
				++nbIncomingConnections;} 
	}
    unsigned int expectedIncomingConnections(CONNECTION_RATIO*sim.get_NbNeurones());
    EXPECT_EQ(expectedIncomingConnections, nbIncomingConnections );
}*/



int main (int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
