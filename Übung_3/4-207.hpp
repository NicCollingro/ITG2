struct B; // Deklariere hier, damit A es kennt

struct A {
    double a;
    A();
    A(double x);
    A(B &x);
};

struct B {
    double b;
    B();
    B(A &x);
    operator A();
};
