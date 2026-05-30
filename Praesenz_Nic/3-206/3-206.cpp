//Speed Test

using namespace std;
#include <iostream>
#include <stdio.h>
#include <time.h>

timespec ts;
double time0;

void set_zerotime(){
	clock_gettime(CLOCK_REALTIME, &ts);
	time0 = ts.tv_sec+1.e-9*ts.tv_nsec;
}

double print_time(){
	clock_gettime(CLOCK_REALTIME, &ts);
	double dt = ts.tv_sec+1.e-9*ts.tv_nsec-time0;
	printf ("dT=%11.8fs\n",dt) ;
	return (dt);
}

class cnum{
	public:
		double x[100000];
		cnum(double a=0){x[0]=1;}
		cnum operator+(cnum a){return (cnum(x[0]+a.x[0]));} // CbV
		cnum operator+(cnum* a){return (cnum(x[0]+a->x[0]));} // CbP
		cnum operator-(cnum& a){return (cnum(x[0]+a.x[0]));} //CbR
};

int& maxwert(int a, int b){
	if (a>b) return a;
	else return b;
}


int main(){
	cnum z1(1), z2;

	set_zerotime();
	for (int i=0; i<10000; i++){
		z2=z2+z1;}

	cout << "Call-by-Value: 		";
	print_time();

	set_zerotime();
	for (int i=0; i<10000; i++){
		z2 = z2+&z1;
	}
	cout << "Call-by-Pointer: 		";
	print_time();

	set_zerotime();
	for (int i=0; i<10000; i++){
		z2 = z2-z1;
	}
	cout << "Call-by-Reference:		";
	print_time();

	int x=17, y=4;
	int& z = maxwert(x,y);
	cout << z << endl;

	int w=maxwert(y,x);
	cout << z << endl;

	return 0;
}
