#include <iostream>
#include <cmath>
#include "Simulation.hpp" // refaire le chemin car pas dans le meme repertoire


simulation sim(2);
sim.CreateConnection(0,1);
sim.RunSimulation(1);

//n1(0); //pas de courant externe
//n2(1,1.5)

EXPECT_EQ(0, sim.getNeuronePotential(0));
EXPECT_EQ(1.0*20*(1-exp(-0.1/20)), sim.getNeuronePotential(1));


//potential_ = C1*potential_ + I_ext_*C2 + buffer_[(local_clock_)%Delay_]; 
