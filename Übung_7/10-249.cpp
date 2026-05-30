using namespace std;
#include <iostream>
#include <math.h>

//Prototypen
long ausdruck(char&);
long summand(char&);
long faktor(char&);
long zahl(char&);
long fak(long);
long x[26] = {0};


int main(){
    char c;
    bool ende = false;

    while(!ende){
        cout << "\n >> "; //Erzeugt einen Promt '>>' zur  Eingabe cin.get(c) liest ein Zeichen aus dem Tastaturpuffer ein
        cin.get(c);
        switch(c){
            case '\n': ende=true; break;
            case ':': {cin.get(c); int j = c-'a'; cin.get(c); cin.get(c);  x[j] = ausdruck(c); break;} //2 mal cin um das "=" zu skippen
            default : cout << ausdruck(c); break; //Starte Rekursion
        }
    }
}

long ausdruck(char& c){
    long a = 0;

    switch(c){
        case '+': cin.get(c); a= +summand(c); break;
        case '-': cin.get(c); a= -summand(c); break;
        default : a = summand(c); break;
    }

    while(c== '+' || c== '-')
        switch(c){
            case '+': cin.get(c); a += summand(c); break;
            case '-': cin.get(c); a -= summand(c);break;
        }
    return a;
}

long summand(char& c){
    long s = faktor(c);

    while(c == '*' || c == '/')
        switch(c){
            case '*': cin.get(c); s *= faktor(c); break;
            case '/': cin.get(c); s/= faktor(c); break;
        }

    return s;
}

long faktor(char& c){
    long f;
    switch (c){
        case '(': cin.get(c); f=ausdruck(c); switch(c){case')': cin.get(c); break;  default: cout << "Rechte Klammer fehlt!\n"; break;} break;
        case '#': cin.get(c); f = -faktor(c); break;
        default: f=zahl(c);break;
    }

    //while und if Abfragen um die Prioritäten von ! und ^ festzulegen. Andernfalls kommt es zu dem in der Aufgabenstellung beschriebenen Problem.
    //while damit ich 3!! einlesen kann. Für ^ soll ja nicht ^^Faktor möglich sein.
    while(c == '!'){
        cin.get(c);
        f = fak(f);
    }
    if(c == '^'){
        cin.get(c);
        long exp = faktor(c);
        f = pow(f, exp);
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

    if(islower(c)){ //analogon zu isdigit
        int i = c-'a';
        cin.get(c);
        return x[i];
    }
    while(isdigit(c)){
        z = 10*z + long(c-'0');
        cin.get(c);
    }
    return z;
}
