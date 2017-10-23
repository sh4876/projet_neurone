#include <iostream>
#include <cmath>
#include <vector>
#include "Neuron.hpp"
#include "Constants.hpp"
#include "Simulation.hpp"

using namespace std;
//{}
// []


//void CurrentRegulation (int current, int tempsactuel, int tempsSimulation);


int main (){
	
	Simulation S1(2);
	S1.RunSimulation();

	
	return 0;
}


/*void CurrentRegulation (int current, int tempsactuel, int tempsSimulation ) {
	if (tempsactuel>tempsSimulation)
	current = 0;
}
*/

