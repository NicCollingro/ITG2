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
  person *prev;
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
  temp->next = nullptr;
  temp->prev = nullptr;
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
    temp->next->prev =
        temp; // Setze prev eintrag für die neue Person bevor temp geändert wird
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

  while (run->next != nullptr) {
    run = run->next;
    print_person(run);
  }

  cout << "============================\n";
}

// Fügt eine Person an der richtigen Stelle ein
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
  temp->prev = run;
  if (temp->next != nullptr)
    temp->next->prev = temp;
  run->next = temp;

  return 1;
}

int remove_person() {
  string rm_name, vorname, nachname; // Name der Person die entfernt werden soll
  uint16_t rm_gebjahr; // uint16_t Geburtsjahr der Person, die entfernt werden
                       // soll (falls zwei Personen gleichen Namen haben)

  // Falls Liste leer, beende while Schleife in main da remove_person() dann
  // nichts macht
  if (root == nullptr) {
    cout << "Liste ist Leer";
    return 0;
  }

  cout << "Vorname der Person, die entfernt werden soll ('-' zum Beenden): ";
  cin >> vorname;

  if (vorname == "-")
    return 0;

  cout << "Nachname: ";
  cin >> nachname;

  cout << "Geburtsjahr: ";
  cin >> rm_gebjahr;

  rm_name = vorname + " " + nachname;

  person *temp = root;
  run = nullptr; // In case root is the person to be removed
  while (!(temp->name == rm_name && temp->gebjar == rm_gebjahr)) {
    if (temp->next == nullptr) {
      cout << "\033[31mPerson nicht gefunden!\033[0m" << endl;
      return 1;
    }

    run = temp;
    temp = temp->next;
  }

  // Falls die zu löschende Person = root -> setze root = root->next
  if (temp == root) {
    root = root->next;
    // setze prev = nullptr, da neuer root
    if (root != nullptr)
      root->prev = nullptr;
  }

  // Falls die Person gefunden wurde -> run->next auf temp->next (um lücke in
  // liste zu fixen)
  else
    run->next = temp->next;

  // Setze neues prev des Nachfolgers, falls vorhanden
  if (temp->next != nullptr)
    temp->next->prev = temp->prev;

  // Lösche Person und printe Erfolgsmeldung
  delete temp;
  cout << "\033[32mDie Person " << rm_name << " (Geburtsjahr " << rm_gebjahr
       << ") wurde gelöscht!\033[0m" << endl;

  return 1;
}

int print_older_than() {
  string start_name, vorname, nachname;
  uint16_t start_gebjahr;

  // Falls Liste leer, beende while Schleife in main da remove_person() dann
  // nichts macht
  if (root == nullptr) {
    cout << "Liste ist Leer";
    return 0;
  }

  cout << "Vorname der Person, ab der die älteren Personen gefunden werden "
          "sollen ('-' zum Beenden): ";
  cin >> vorname;

  if (vorname == "-")
    return 0;

  cout << "Nachname: ";
  cin >> nachname;

  cout << "Geburtsjahr: ";
  cin >> start_gebjahr;

  start_name = vorname + " " + nachname;

  // Gehe zur Person, ab der gestartet werden soll
  run = root;
  while (!(run->name == start_name && run->gebjar == start_gebjahr)) {

    // Falls Listenende erreicht und Person nicht gefunden -> Fehlermeldung
    if (run->next == nullptr) {
      cout << "\033[31mPerson nicht gefunden!\033[0m" << endl;
      return 1;
    }

    run = run->next;
  }

  // Falls Person gefunden -> Alle älteren Personen ausgeben
  person *temp = run->prev;

  cout << "============================\n";
  while (temp != nullptr) {
    print_person(temp);
    temp = temp->prev;
  }
  cout << "============================\n";

  return 1;
}

int main() {
  init_list();
  print_list();

  while (add_person()) {
  }

  print_list();

  while (remove_person()) {
  }

  print_list();

  while (print_older_than()) {
  }
}
