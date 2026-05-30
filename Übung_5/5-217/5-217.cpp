#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

class Fkt{
	public:
		int p;
		virtual double operator()(double x)=0; //instanziierung einer virtuellen Methode wie in Aufgabenstellung verlangt
};

class Poly: public Fkt{ // das public vor Fkt hätte man sich gespart wenn FKT ein struct wäre
	public:
		Poly(int deg) {p=deg;} //Cstr für poly mit grad des polynoms
		double operator()(double x){return pow(x,p);} //x^p
};

class Root: public Fkt{
	public:
		Root(int nroot){p=nroot;}
		double operator()(double x){return pow(x, 1./p);}
};

int main(){
	Fkt* f[5];

	f[0] = new Poly(1);
	f[1] = new Poly(2);
	f[2] = new Root(2);
	f[3] = new Poly(3);
	f[4] = new Root(3);

	for(double x=0.; x<2.; x+=0.01){
		printf("%8.2f ", x);
		for (int i=0; i<5; ++i){
			printf("%8.2f ", (*f[i])(x));
		}
		cout << endl;
	}
}
