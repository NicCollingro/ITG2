#include <iostream>
using namespace std;

int f(int a) {return 1;}
int g(int& a) {return 2;}
int h(int*a) {return 3;}

int x=0;
int* y = &x;

int main(){
	cout << f(x) << " ";
//	cout << f(y) << " ";  Hier wird ein Pointer (auf x) einer Funktion übergeben die einen Integer wert erwartet.

//	cout << f(*x) << " "; x ist kein Pointer -> kann nicht Dereferenziert werden. 
	cout << f(*y) << " "; // *y Dereferenziert pointer -> int

//	cout << f(&x) << " "; &x vom Typ int* , funktion erwartet int 
//	cout << f(&y) << " "; &y vom Typ int** (pointer auf pointer), funktion erwartet int

	cout << g(x) << " "; // funktion erwartet Referenz auf int, x wird referenziert
//	cout << g(y) << " "; y ist pointer, kein int

//	cout << g(*x) << " "; x kein Pointer -> kann nicht Dereferenziert werden
	cout << g(*y) << " "; // y ist Pointer, wird Dereferenziert als Referenz übergeben.

//	cout << g(&x) << " "; ist Pointer kein int&
//	cout << g(&y) << " "; -"-

//	cout << h(x) << " "; x ist int, kein Pointer
	cout << h(y) << " ";

//	cout << h(*x) << " "; again: x kein Pointer, kann nicht Dereferenziert werden
//	cout << h(*y) << " "; *y ist int, kein Pointer

	cout << h(&x) << " ";
//	cout << h(&y) << " "; ist int** und kein int*
}
