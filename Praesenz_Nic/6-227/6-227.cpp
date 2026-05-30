#include <iostream>
#include <math.h>
#include <stdio.h>
#include <complex>
using namespace std;

template<class T=double, size_t n=1>
class Vector{
	private:
		size_t pos = n;

	public:
		T elem[n];

		Vector(){
			for(size_t i=0; i<n; i++){
				elem[i]=0;
			}
		}

		template<typename T1>
		Vector(T1 erst){
			elem[--pos]=erst;}

		template<typename T1, typename... T2>
		Vector(T1 erst, T2... rest) : Vector(rest...){
			elem[--pos] = erst;}

		Vector<T,n> operator+(const Vector<T,n>& v){
			Vector<T, n> tmp;
			for(size_t i=0; i<n; i++){
				tmp.elem[i] = (*this).elem[i] + v.elem[i];
			}
			return tmp;
		}
};

template<class T=double, size_t n=1> 
	ostream& operator<<(ostream& s, const Vector<T,n>& v){
		cout << "[" << v.elem[0];
		for(size_t i=0; i<n-1; i++){
			cout << "," << v.elem[i+1];
		}
		cout << "]";
		return(s);
	};

template<class T=double, size_t n=1>
	double abs(const Vector<T, n>& v){
		double tmp = 0;
		for(size_t i=0; i<n; i++){
			tmp += abs(v.elem[i]) * abs(v.elem[i]);
		}
		return sqrt(tmp);
	};

int main() {
  Vector<double,4> u1(1,2,3,4), u2(10,20,30,40), u3 = u1 + u2;
  cout << u1 << endl << u2 << endl << u3 << endl << u1 + u2 + u3 << endl;
  cout << abs(u3) << "\n\n";
  
  Vector<Vector<double,4>,2> v1(u1,u2), v2(u2,u3), v3 = v1 + v2;
  cout << v1 << endl << v2 << endl << v3 << endl << v1 + v2 + v3 << endl;
  cout << abs(v3) << "\n\n";
  
  complex<double> z1(1,2), z2(3,4), z3 = z1 + z2;
  Vector<complex<double>,4> w1(z1,z2,z3,z1+z2), w2(z1,z2,z3+z1,z1), w3(1,1,1,complex<double>(0,-1));
  cout << w1 << endl << w2 << endl << w3 << endl << w1 + w2 + w3 << endl;
  cout << abs(w3) << "\n\n";
}
