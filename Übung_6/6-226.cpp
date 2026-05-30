#include<iostream>
#include<vector>

using namespace std;

vector<int> merge(vector<int> a, vector<int> b); //Forward Deklaration

vector<int> mergecall (vector<int> a){
	if(a.size() <= 1){
		return a;
	}
	else{
		vector<int> leftHalf(a.begin(), a.begin()+a.size()/2);
		vector<int> rightHalf(a.begin() + a.size()/2, a.end());

		leftHalf = mergecall(leftHalf);
		rightHalf = mergecall(rightHalf);

		return(merge(leftHalf, rightHalf));
	}
}


vector<int> merge (vector<int> a, vector<int> b){
	vector<int> newVec;
	while(a.size() != 0 && b.size() != 0){
		if(a.front() <= b.front()){
			newVec.push_back(a.front());
			a.erase(a.begin());
		}
		else{
			newVec.push_back(b.front());
			b.erase(b.begin());
		}
	}
	while(a.size() != 0){
		newVec.push_back(a.front());
		a.erase(a.begin());
	}
	while(b.size() != 0){
		newVec.push_back(b.front());
		b.erase(b.begin());
	}
	return newVec;
}

void print_vector(vector<int> a){
	for(int i=0; i<a.size()-1; i++){
		cout << a[i] << ", ";
	}
	cout << a[a.size()] << " " << endl;
}

int main() {
  vector<int> feld = {7,5,3,9,2,10,3,12,-1,8,7,3,4,10,10,-4};
  print_vector(feld);
  feld = mergecall(feld);
  print_vector(feld);
}
