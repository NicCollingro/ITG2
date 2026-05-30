#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
using namespace std;

//  cmdstr : haelt einen Kommando-String und einen Lesekopf.
//  Werte sind jetzt double.
class cmdstr {
public:
  vector<char> str;   // bereinigter String
  size_t       pos;   // Lesekopf
  char         var;   // freie Variable (nur bei Funktionsdefinitionen)

  cmdstr() : pos(0), var(0) {}

  // aus std::string, strippt Blanks/Tabs/'\0' per Iterator
  cmdstr(const string& s, char v = 0) : pos(0), var(v) {
    for (string::const_iterator it = s.begin(); it != s.end(); ++it)
      if (*it != ' ' && *it != '\t' && *it != '\0')
        str.push_back(*it);
  }
  // aus vector<char>, ebenfalls strippend
  cmdstr(const vector<char>& vc, char v = 0) : pos(0), var(v) {
    for (vector<char>::const_iterator it = vc.begin(); it != vc.end(); ++it)
      if (*it != ' ' && *it != '\t' && *it != '\0')
        str.push_back(*it);
  }

  char zeichen() const { return pos < str.size() ? str[pos] : '\0'; }
  void vor()           { if (pos < str.size()) ++pos; }
  void reset()         { pos = 0; }
  bool leer()  const   { return str.empty(); }
  string text() const  { return string(str.begin(), str.end()); }

  // freie Variable durch (n) ersetzen -- volle double-Genauigkeit, kein 'e'
  cmdstr subst(double n) const {
    string ns = to_string(n);   // 6 Nachkommastellen -- wie Aufgabenstellung
    cmdstr res; res.var = var;
    for (size_t i = 0; i < str.size(); ++i) {
      if (str[i] == var && var != 0) {
        res.str.push_back('(');
        for (size_t j = 0; j < ns.size(); ++j) res.str.push_back(ns[j]);
        res.str.push_back(')');
      } else res.str.push_back(str[i]);
    }
    return res;
  }
};

// Prototypen
double ausdruck(cmdstr&);
double summand(cmdstr&);
double faktor(cmdstr&);
double zahl(cmdstr&);
double fak(double);
double funktion(char, double);
void   definition(cmdstr&);

map<char, cmdstr> fktlist;     // Funktionsname -> Rumpf (eigenes cmdstr)
map<char, double> constlist;   // Konstantenname -> Wert
vector<cmdstr>    history;     // alle ausgewerteten Ausdruecke

// Wert eines History-Eintrags durch Neu-Auswertung (auf Kopie) bestimmen
double history_wert(size_t i) {
  cmdstr h = history[i];
  h.reset();
  return ausdruck(h);
}

void definition(cmdstr& cs) {
  char c = cs.zeichen();
  if (islower(c)) {                          // LowerLetter '=' Ausdruck
    char name = c; cs.vor();
    if (cs.zeichen() == '=') cs.vor();
    constlist[name] = ausdruck(cs);
  } else if (isupper(c)) {                   // UpperLetter '(' LowerLetter ')' '=' Ausdruck
    char fname = c; cs.vor();
    if (cs.zeichen() == '(') cs.vor(); else cout << "Linke Klammer fehlt!\n";
    char var = cs.zeichen(); cs.vor();
    if (cs.zeichen() == ')') cs.vor(); else cout << "Rechte Klammer fehlt!\n";
    if (cs.zeichen() == '=') cs.vor();
    cmdstr rumpf; rumpf.var = var;           // Rest = Rumpf (eigenes Objekt)
    for (size_t i = cs.pos; i < cs.str.size(); ++i) rumpf.str.push_back(cs.str[i]);
    fktlist[fname] = rumpf;
  } else cout << "Fehler bei Definition!\n";
}

double ausdruck(cmdstr& cs) {
  double a;
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

double summand(cmdstr& cs) {
  double s = faktor(cs);
  while (cs.zeichen() == '*' || cs.zeichen() == '/' || cs.zeichen() == '%')
    switch (cs.zeichen()) {
      case '*': cs.vor(); s *= faktor(cs);          break;
      case '/': cs.vor(); s /= faktor(cs);          break;
      case '%': cs.vor(); s  = fmod(s, faktor(cs)); break;
    }
  return s;
}

double faktor(cmdstr& cs) {
  double f = 0;
  char c = cs.zeichen();

  if (isupper(c)) {                          // UpperLetter '(' Ausdruck ')'
    char fname = c; cs.vor();
    if (cs.zeichen() == '(') {
      cs.vor();
      double arg = ausdruck(cs);
      if (cs.zeichen() == ')') cs.vor(); else cout << "Rechte Klammer fehlt!\n";
      f = funktion(fname, arg);
    } else cout << "Linke Klammer fehlt!\n";
  }
  else if (c == '[') {                       // '[' Ausdruck ']'  -> History-Referenz
    cs.vor();
    double idxd = ausdruck(cs);
    if (cs.zeichen() == ']') cs.vor(); else cout << "Rechte Klammer fehlt!\n";
    int i = (int)idxd;
    if (i >= 0 && i < (int)history.size()) f = history_wert(i);
    else cout << "Ungueltiger History-Index " << i << "!\n";
  }
  else if (islower(c)) {                     // LowerLetter -> Konstante
    map<char,double>::iterator it = constlist.find(c);
    if (it != constlist.end()) f = it->second;
    else cout << "Unbekannte Konstante " << c << "!\n";
    cs.vor();
  }
  else if (c == '(') {                       // '(' Ausdruck ')'
    cs.vor();
    f = ausdruck(cs);
    if (cs.zeichen() == ')') cs.vor(); else cout << "Rechte Klammer fehlt!\n";
  }
  else f = zahl(cs);                         // Zahl

  while (cs.zeichen() == '!') { cs.vor(); f = fak(f); }       // Fakultaet
  if    (cs.zeichen() == '^') { cs.vor(); f = pow(f, faktor(cs)); }  // Potenz

  return f;
}

double zahl(cmdstr& cs) {                    // Ziffer+ [ (.|,) Ziffer+ ]
  double z = 0;
  while (isdigit(cs.zeichen())) { z = 10*z + (cs.zeichen()-'0'); cs.vor(); }
  if (cs.zeichen() == '.' || cs.zeichen() == ',') {
    cs.vor();
    double frac = 0, scale = 1;
    while (isdigit(cs.zeichen())) { frac = 10*frac + (cs.zeichen()-'0'); scale *= 10; cs.vor(); }
    z += frac / scale;
  }
  return z;
}

double fak(double n) { return tgamma(n + 1.0); }   // n! = Gamma(n+1)

double funktion(char name, double arg) {
  map<char,cmdstr>::iterator it = fktlist.find(name);
  if (it == fktlist.end()) { cout << "Unbekannte Funktion " << name << "!\n"; return 0; }
  cmdstr rumpf = it->second.subst(arg);      // var -> (arg)
  return ausdruck(rumpf);
}

void zeige_definitionen() {
  cout << "   FUNCTIONS:\n";
  for (map<char,cmdstr>::iterator it = fktlist.begin(); it != fktlist.end(); ++it) {
    string b = it->second.text();
    char v = it->second.var;
    for (size_t i = 0; i < b.size(); ++i) if (b[i] == v) b[i] = 'x';  // Variable als x zeigen
    cout << " def: " << it->first << "(x) = " << b << "\n";
  }
  cout << "   CONSTANTS:\n";
  for (map<char,double>::iterator it = constlist.begin(); it != constlist.end(); ++it)
    cout << " def: " << it->first << " = " << to_string(it->second) << "\n";
}

void zeige_history() {
  cout << "   HISTORY:\n";
  for (size_t i = 0; i < history.size(); ++i)
    cout << " [" << i << "]   " << history[i].text() << "  = " << history_wert(i) << "\n";
}

int main() {
  string line;
  while (true) {
    cout << ">> ";
    if (!getline(cin, line)) break;
    cmdstr cs(line);
    if (cs.leer()) continue;

    char first = cs.zeichen();
    if (first == ';') { zeige_history(); continue; }
    if (first == ':') {
      cs.vor();
      if (cs.zeichen() == '\0') zeige_definitionen();   // ':' allein
      else                      definition(cs);          // ':' Definition
      continue;
    }
    // Ausdruck: auswerten, ausgeben, in History ablegen
    cmdstr expr = cs;                 // Kopie mit pos = 0 fuer die History
    double v = ausdruck(cs);
    cout << " " << expr.text() << " = " << v << "\n";
    history.push_back(expr);
  }
  return 0;
}
