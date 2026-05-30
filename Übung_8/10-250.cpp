#include <math.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class cmdstr {
public:
  vector<char> str;   // der bereinigte String
  size_t       pos;   // Position des Lesekopfs
  char         var;   // freie Variable (nur bei Funktionsdefinitionen belegt)

  // Default-Konstruktor
  cmdstr() : pos(0), var(0) {}

  // Konstruktor aus std::string  -- strippt Blanks und '\0' beim Einlesen.
  // (verwendet Iteratoren der string-Klasse)
  cmdstr(const string& s, char v = 0) : pos(0), var(v) {
    for (string::const_iterator it = s.begin(); it != s.end(); ++it)
      if (*it != ' ' && *it != '\t' && *it != '\0')
        str.push_back(*it);
  }

  // Konstruktor aus vector<char>  -- ebenfalls strippend.
  // (verwendet Iteratoren der vector<char>-Klasse)
  cmdstr(const vector<char>& v, char vr = 0) : pos(0), var(vr) {
    for (vector<char>::const_iterator it = v.begin(); it != v.end(); ++it)
      if (*it != ' ' && *it != '\t' && *it != '\0')
        str.push_back(*it);
  }

  // Zugriff auf das aktuelle Zeichen (Position des Lesekopfs)
  char zeichen() const { return pos < str.size() ? str[pos] : '\0'; }

  // Vorwärts immer, Rückwärts nimmer!
  void vor() { if (pos < str.size()) ++pos; }

  //DOCH RÜCKWÄRTS???
  void zurück(){if (pos > 0) --pos;}

  bool leer() const { return str.empty(); }

  // subst: setzt an jeder Stelle der freien Variable den Zahlenwert n ein,
  // und zwar in der Form  x -> (n), da das Substitut auch negativ sein kann,
  // an dieser Stelle im Parsebaum aber kein Unärer +/- erwartet werden kann.
  cmdstr subst(long n) const {
    cmdstr res;
    res.var = var;
    string ns = to_string(n);
    for (size_t i = 0; i < str.size(); ++i) {
      if (str[i] == var && var != 0) {
        res.str.push_back('(');
        for (size_t j = 0; j < ns.size(); ++j) res.str.push_back(ns[j]);
        res.str.push_back(')');
      } else {
        res.str.push_back(str[i]);
      }
    }
    return res;
  }
};


// Prototypen
long kommando(cmdstr&);
void definition(cmdstr&);
long ausdruck(cmdstr&);
long summand(cmdstr&);
long faktor(cmdstr&);
long zahl(cmdstr&);
long fak(long);
long funktion(char, long);

// map-Container: Funktionsname -> zugehoeriger cmdstr (eigenes Objekt je Fkt.)
map<char, cmdstr> fktlist;
// map-Container: Konstantenname -> ausgewerteter Wert
map<char, long>   constlist;

long kommando(cmdstr& cs) {
  long k = 0;
  switch (cs.zeichen()) {
    case ':':  cs.vor(); definition(cs); break;   // ':' Definition
    default:   k = ausdruck(cs);          break;   // Ausdruck
  }
  return k;
}
void definition(cmdstr& cs) {
  char c = cs.zeichen();

  if (islower(c)) {
    // Konstante:  LowerLetter '=' Ausdruck
    char name = c;
    cs.vor();
    if (cs.zeichen() == '=') cs.vor();
    constlist[name] = ausdruck(cs);            // Wert sofort auswerten & ablegen
  }
  else if (isupper(c)) {
    // Funktion:  UpperLetter '(' LowerLetter ')' '=' Ausdruck
    char fname = c;
    cs.vor();
    if (cs.zeichen() == '(') cs.vor();
    else cout << "Linke Klammer fehlt!\n";
    char var = cs.zeichen();                   // freie Variable
    cs.vor();
    if (cs.zeichen() == ')') cs.vor();
    else cout << "Rechte Klammer fehlt!\n";
    if (cs.zeichen() == '=') cs.vor();

    // Rest des Strings ist der Funktionsrumpf (Ausdruck) -> eigenes cmdstr.
    // Der Rumpf wird NICHT sofort ausgewertet, sondern erst beim Aufruf.
    cmdstr rumpf;
    rumpf.var = var;
    for (size_t i = cs.pos; i < cs.str.size(); ++i)
      rumpf.str.push_back(cs.str[i]);
    fktlist[fname] = rumpf;
  }
  else {
    cout << "Fehler bei Definition!\n";
  }
}

long ausdruck(cmdstr& cs) {
  long a;
  switch (cs.zeichen()) {
    case '+': cs.vor(); a = +summand(cs); break;
    case '-': cs.vor(); a = -summand(cs); break;
    default:            a =  summand(cs); break;
  }
  while (cs.zeichen() == '+' || cs.zeichen() == '-')
    switch (cs.zeichen()) {
      case '+': cs.vor(); a += summand(cs); break;
      case '-': cs.vor(); a -= summand(cs); break;
    }
  return a;
}

long summand(cmdstr& cs) {
  long s = faktor(cs);
  while (cs.zeichen() == '*' || cs.zeichen() == '/' || cs.zeichen() == '%')
    switch (cs.zeichen()) {
      case '*': cs.vor(); s *= faktor(cs);      break;
      case '/': cs.vor(); s /= faktor(cs);      break;
      case '%': cs.vor(); s  = s % faktor(cs);  break;
    }
  return s;
}

long faktor(cmdstr& cs) {
  long f = 0;
  char c = cs.zeichen();

  if (isupper(c)) {
    // Funktionsaufruf:  UpperLetter '(' Ausdruck ')'
    char fname = c;
    cs.vor();
    if (cs.zeichen() == '(') {
      cs.vor();
      long arg = ausdruck(cs);
      if (cs.zeichen() == ')') cs.vor();
      else cout << "Rechte Klammer fehlt!\n";
      f = funktion(fname, arg);
    } else cout << "Linke Klammer fehlt!\n";
  }
  else if (islower(c)) {
    // Konstante:  LowerLetter
    map<char, long>::iterator it = constlist.find(c);
    if (it != constlist.end()) f = it->second;
    else cout << "Unbekannte Konstante " << c << "!\n";
    cs.vor();
  }
  else if (c == '(') {
    cs.vor();
    f = ausdruck(cs);
    if (cs.zeichen() == ')') cs.vor();
    else cout << "Rechte Klammer fehlt!\n";
  }
  else {
    f = zahl(cs);
  }

  while (cs.zeichen() == '!') { cs.vor(); f = fak(f); }
  if    (cs.zeichen() == '^') { cs.vor(); f = pow(f, faktor(cs)); }

  return f;
}

long zahl(cmdstr& cs) {
  long z = 0;
  while (isdigit(cs.zeichen())) {
    z = 10 * z + long(cs.zeichen() - '0');
    cs.vor();
  }
  return z;
}

long fak(long n) {
  if (n > 1) return n * fak(n - 1);
  else return 1;
}

// Wertet eine zur Laufzeit definierte Funktion aus:
// Rumpf holen, freie Variable durch (arg) substituieren, dann parsen.
long funktion(char name, long arg) {
  map<char, cmdstr>::iterator it = fktlist.find(name);
  if (it == fktlist.end()) {
    cout << "Unbekannte Funktion " << name << "!\n";
    return 0;
  }
  cmdstr rumpf = it->second.subst(arg);   // x -> (arg)
  return ausdruck(rumpf);                 // frischer Parser-Aufruf
}

int main() {
  string line;
  while (getline(cin, line)) {            // ganze Zeile inkl. Leerzeichen lesen
    cmdstr cs(line);                      // beim Umwandeln Blanks entfernen
    if (cs.leer()) continue;

    bool ist_definition = (cs.str[0] == ':');
    long result = kommando(cs);
    if (!ist_definition)                  // nur Ausdruecke liefern Ausgabe
      cout << result << '\n';
  }
  return 0;
}
