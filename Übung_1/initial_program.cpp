#include <inttypes.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

// Datenstruktur
struct person {
  string name;
  uint16_t gebtag;
  uint16_t gebmon;
  uint16_t gebjar; // uint16_t = unsigned int mit 16 Bit
  person *next;
};

// Zeiger auf den Listenanfang und auf das durchlaufende aktuelle Element
person *root;
person *run;

// Einige (nach Geburtsjahr sortierte) Vorabeinträge für die Liste
#define ANZAHL 6

string list_name[ANZAHL] = {
    "JHVH",       "Konrad Zuse",     "Tim OReilly",
    "Bill Gates", "Mark Zuckerberg", "Michel de Notredame"};

uint16_t list_gebtag[ANZAHL] = {1, 22, 6, 28, 14, 31};
uint16_t list_gebmon[ANZAHL] = {1, 6, 6, 10, 5, 12};
uint16_t list_gebjar[ANZAHL] = {0, 1910, 1954, 1955, 1984, 3600};

// Liefert eine leere Datenstruktur zurück
person *gen_person() {
  person *temp = new person;
  temp->name = "";
  temp->gebtag = 0;
  temp->gebmon = 0;
  temp->gebjar = 0;
  temp->next = NULL;
  return temp;
}

// Erzeugt aus den Vorabdaten eine Liste
void init_list() {
  person *temp = gen_person();
  root = temp;

  root->name = list_name[0];
  root->gebtag = list_gebtag[0];
  root->gebmon = list_gebmon[0];
  root->gebjar = list_gebjar[0];

  for (int i = 1; i < ANZAHL; i++) {
    temp->next = gen_person();
    temp = temp->next;

    temp->name = list_name[i];
    temp->gebtag = list_gebtag[i];
    temp->gebmon = list_gebmon[i];
    temp->gebjar = list_gebjar[i];
  }
}

// Formatierte Ausgabe der Daten in der Datenstruktur start
void print_person(person *start) {
  printf("%02d.%02d.%04d ", start->gebtag, start->gebmon, start->gebjar);
  cout << start->name << endl;
}

// Hangelt sich entlang der Liste und gibt alle Einträge aus
void print_list() {
  cout << "============================\n";
  run = root;
  print_person(run);

  while (run->next != NULL) {
    run = run->next;
    print_person(run);
  }

  cout << "============================\n";
}

// Fügt eine Persostd::cout << a << std::endl;n an der richtigen Stelle ein
int add_person() {
  string nname, vorname, nachname;
  uint16_t ngebjar;

  cout << "Vorname ('-' zum Beenden): ";
  cin >> vorname;
  if (vorname == "-")
    return 0;

  cout << "Nachname: ";
  cin >> nachname;

  nname = vorname + " " + nachname;

  cout << "Jahr: ";
  cin >> ngebjar;

  run = root;
  while (!(run->gebjar <= ngebjar && run->next->gebjar >= ngebjar)) {
    run = run->next;
  }

  person *temp = gen_person();
  temp->name = nname;
  temp->gebjar = ngebjar;

  temp->next = run->next;
  run->next = temp;

  return 1;
}

int main() {
  init_list();
  print_list();

  while (add_person()) {
  }

  print_list();
}
