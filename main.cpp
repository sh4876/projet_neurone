#include <iostream>
#include <cmath>
#include "Neuron.cpp"
#include "Constants.hpp"


using namespace std;
//{}


void CurrentRegulation (int current);
void UpdateSimulation (int tempsSimulation); /*temps simulation egal le 
temps actuel de l experience, update sim devrait etre apellée tous les
pas de temps et non apres increment*pas de temps */


int main (){
	Neuron neurone1;
	int SimulationTime (SimulationStart);
		while (SimulationTime>SimulationStop) {
		}	
	return 0;
	}

void CurrentRegulation (int current, int tempsSimulation ) {
	if (tempsSimulation>tempsSimulation + h)
	current = 0;
	}
	
void UpdateSimulation (int tempsSimulation, int increment, Neuron neurone) {
	tempsSimulation += increment*h;
	neurone.update(increment);
	
	}
