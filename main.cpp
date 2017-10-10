#include <iostream>
#include <cmath>
#include "Neuron.hpp"
#include "Constants.hpp"


using namespace std;
//{}


void CurrentRegulation (int current);
void UpdateSimulation (double& globalClock, int increment, Neuron& neurone); /*temps simulation egal le 
temps actuel de l experience, update sim devrait etre apellée tous les
pas de temps et non apres increment*pas de temps */


int main (){
	Neuron neurone1;
	double global_clock(SimulationStart);
	cout << "global_clock" << global_clock << endl;
		while (global_clock<SimulationStop) {
			int increment(0);
			double borneSup((SimulationStop-global_clock)/h);
			cout <<" choisir l increment tq 0 < increment < "<< borneSup << endl;
			cin>> increment;
			if ((increment>borneSup)or(increment <0)) {cout <<"exit erreur d increment "<< endl; 
				return 0;}
			else {
				UpdateSimulation(global_clock, increment, neurone1); }
			
		}	
	return 0;
	}

void CurrentRegulation (int current, int tempsSimulation ) {
	if (tempsSimulation>tempsSimulation + h)
	current = 0;
	}
	
void UpdateSimulation (double& globalClock, int increment, Neuron& neurone) {
	
	double finUpdate(globalClock+increment*h);
		
		while (globalClock < finUpdate) {
		neurone.update();
		globalClock += h;

		cout << "global_clock" << globalClock << endl;
		}
	
}
