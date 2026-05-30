#include <iostream>
using namespace std;
#define EXEC(x)                                                                \
    cout << "\"" << #x << "\"\r\T\t\t\t";                                      \
    x;                                                                         \
    cout << endl;

struct B {
    int b;
    B() : b(1) { cout << "DFLT CTOR B::B()"; }
    B(int x) : b(x) { cout << "CST CTOR B::B(int)"; }
    B(const B &x) : b(x.b) { cout << "COPY CTOR B::B(cont B&)"; }
};

struct A {
    int a;
    A() : a(2) { cout << "DFLT CTOR A::A()"; }
    A(int x) : a(x) { cout << "CAST CTOR A::A(int)"; }
    A(const B &x) : a(x.b) { cout << "CAST CTOR A::A(const B&)"; }
};

A a1(B z) { return (A)z; };
A a2(B(z)) { return (A)z; };

int main() {
    EXEC(B b1; cout << b1.b;)  // ruft B() CTOR auf: "DFLT CTOR B::B() 1"
    EXEC(B(b2); cout << b2.b;) // ruft B() auf, da b2 noch nicht existiert.
                               // "DFLT CTOR B::B() 1"
    EXEC(B b3(8);
         cout << b3.b;) // ruft B(int x):b(x) auf: "CST CTOR B::B(int) 8"
    EXEC(B(b4) = 9; cout << b4.b;) // ruft B(int x):b(x) auf (= wird als ()
                                   // interpretiert): "CST CTOR B::B(int) 9"
    // EXEC (B(b3);) //erzeugt Compilierfehler
    EXEC(B b5 = B(b3); cout << b5.b;) // ruft B(const B& x): b(x.b) auf: "COPY
                                      // CTOR B::B(const B&) 8"
    EXEC(B b6((B)b3); cout << b6.b;)  // gleiches wie obendrüber

    // EXEC (B b7(B(b3));) //erzeugt Compilierfehler (zumindest auf ARM64)
    // EXEC (cout << b7.b;) //erzeugt Compilierfehler
    // EXEC (cout << b7(32).b;) //erzeugt Compilierfehler

    EXEC(cout << a1(42).a;) // ruft a1 auf mit tmp element B(42), d.h. wird CST
                            // CTOR B::B(int) und dann CAST CTOZ A::A(cont B&)
                            // 42 ausgegeben
    EXEC(cout << a1(b3).a;) // ruft a1 mit tmp erzeugter kopie von b3 auf also
                            // COPY CTOR B::B(const B&) und danach wird der Cast
                            // Ctor von A aufgerufen; CAST CTOR A::A(const &B)
                            // und dann der Wert: 8
    EXEC(cout << a2(42).a;) // ruft a2 mit tmp element B(42) auf, analog zu
                            // a1(42).a
    EXEC(cout << a2(b3).a;) // analog zu a2(b3).a
}
