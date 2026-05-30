#include<iostream>
#include<vector>

using namespace std;

vector<double> Vect;

// da Rekursion am ende zu ner double variable werden soll ist der Rückgabetyp entweder ein double ODER void

void sum(int start, int end, double& s0){
	if(end <= start){
		s0 = Vect[start];
	}
	else{
		int mitte = (start+end)/2;
		double s1, s2;
		sum(start, mitte, s1);
		sum(mitte + 1, end, s2);
		s0=s1+s2;
	}
}

int main(){
	Vect = {1,2,3,4,5,6,7,8,9};
	double summe = 0;
	sum(0,Vect.size()-1, summe);
	cout << summe << endl;
}
