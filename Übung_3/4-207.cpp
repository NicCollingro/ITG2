#include "4-207.hpp"
#include <iostream>
using namespace std;

A::A() { cout << "DFLT CTOR A::A()\n"; }
A::A(double x) { cout << "CAST CTOR A::A(double)\n"; }

// Umwandlungs-Konstruktor B -> A.
// In der ersten Variante könnte hier direkt a = -x.b stehen, um Stichpunkt 1 zu
// erfüllen (da wäre B::operator A() obsolet)
// im letzten Aufgabenteil soll aber B::operator A() benutzt werden
A::A(B &x) {
    cout << "CAST CTOR A::A(B&)\n";
    *this = x.operator A();
}

B::B() {
    cout << "DFLT CTOR B::B()\n";
    b = 1;
}
B::B(A &x) { // Beobachtung Stichpunkt 3: Konstruktor wird bevorzugt!
    cout << "CAST CTOR B::B(A&)\n";
    b = -x.a;
}
// Ich lasse hier operator A() drin, da es später für A::A(B &x) gebraucht wird
B::operator A() {
    cout << "CAST OTOR B::operator A()\n";
    return A(-b);
}

int main() {
    cout << endl << "A z1;\n";
    A z1;

    cout << endl << "B z2;\n";
    B z2;

    cout << endl << "z2 = B(z1);\n";
    z2 = B(z1);

    cout << endl << "z1 = A(z2);\n";
    z1 = A(z2);
}
