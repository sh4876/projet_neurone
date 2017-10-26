#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "Constants.hpp"

using namespace std;

//{}



typedef vector<double> Buffer;

class Neuron {
	
	private :
	
	double I_ext_;
	int Delay_;
	double potential_;
	int spikeNumber_;
	int timeSpike_;
	int local_clock_;
	
	
	bool isRefractory(const int&) const; //dit si le neurone est en periode refractaire a un temps donné
	void storePotential (ofstream& out ) const; 
	
	protected : 
	Buffer buffer_;
	
	public :
	
	//Neuron(  double I_ext= I , int Delay=STEP_D, double potential=Vr,   int local_clock=0); // initialisation$
	Neuron(  double I_ext, double Delay, double potential, int local_clock); // initialisation$
	virtual ~Neuron();
	double getPotential() const;
	int getSpikeNumber() const;
	int getTimeSpike() const;
	virtual void writeinBuffer(const int& time ) =0  ; //pas virtuelle pure pour pouvoir faire des tests sur des neurones (sans specificite) //ou bien si 
	void set_Iext(double) ;
	
	bool update () ; 
	
};

/*The GNU C++ compiler has to make a decision where to put the vtable in case you have the definition of the virtual functions 
 * of an object spread across multiple compilations units (e.g. some of the objects virtual functions definitions are in a .cpp 
 * file others in another .cpp file, and so on).

The compiler chooses to put the vtable in the same place as where the first declared virtual function is defined.

Now if you for some reason forgot to provide a definition for that first virtual function declared in the object 
* (or mistakenly forgot to add the compiled object at linking phase), you will get this error. 
*/
 
#endif
