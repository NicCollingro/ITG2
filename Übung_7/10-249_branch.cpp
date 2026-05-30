using namespace std;
#include <iostream>
#include <math.h>

//Prototypen
long ausdruck(char&);
long summand(char&);
long faktor(char&);
long zahl(char&);
long fak(long);

int main(){
    char c;
    bool ende = false;

    while(!ende){
        cout << "\n >> "; //Erzeugt einen Promt '>>' zur  Eingabe cin.get(c) liest ein Zeichen aus dem Tastaturpuffer ein
        cin.get(c);

        switch(c){
            case '\n': ende=true; break;
            default : cout << ausdruck(c); break; //Starte Rekursion
        }
    }
}

long ausdruck(char& c){
    long a = 0;

    switch(c){
        case '+': cin.get(c); a= +summand(c); cout << "+ "; break;
        case '-': cin.get(c); a= -summand(c); cout << "- "; break;
        default : a = summand(c); break;
    }

    while(c== '+' || c== '-')
        switch(c){
            case '+': cin.get(c); a += summand(c); cout << "+ "; break;
            case '-': cin.get(c); a -= summand(c); cout << "- ";break;
        }
    return a;
}

long summand(char& c){
    long s = faktor(c);

    while(c == '*' || c == '/')
        switch(c){
            case '*': cin.get(c); s *= faktor(c); cout << "* "; break;
            case '/': cin.get(c); s/= faktor(c); cout << "/ "; break;
        }

    return s;
}

long faktor(char& c){
    long f;
    switch (c){
        case '(': cin.get(c); f=ausdruck(c); switch(c){case')': cin.get(c); break;  default: cout << "Rechte Klammer fehlt!\n"; break;} break;
        case '#': cin.get(c); cout << "-"; f = -faktor(c); break;
        default: f=zahl(c);break;
    }

    //while und if Abfragen um die Prioritäten von ! und ^ festzulegen. Andernfalls kommt es zu dem in der Aufgabenstellung beschriebenen Problem.
    //while damit ich 3!! einlesen kann. Für ^ soll ja nicht ^^Faktor möglich sein.
    while(c == '!'){
        cin.get(c);
        f = fak(f);
        cout << "! ";
    }
    if(c == '^'){
        cin.get(c);
        long exp = faktor(c);
        f = pow(f, exp);
        cout << "^ ";
    }
    return f;
}

long fak(long n){
    long result = 1;
    for(long i = 2; i <= n; i++){
        result *= i;
    }
    return result;
}

long zahl(char& c){
    long z = 0;

    while(isdigit(c)){
        z = 10*z + long(c-'0');
        cin.get(c);
    }
    cout << z << " ";
    return z;
}

// hatte vergessen das ab der 4 wieder der normale ohne rpn ausgegebne werden soll, daher die 2. file
