#pragma once
#include <iosfwd>

// Vorwärtsdeklaration für product_proxy
class product_proxy;

/**
 * @class vector3d
 * @brief Implementiert einen Vektor im 3-dimensionalen Raum
 *
 */
class vector3d {
  private:
    // vector-komponenten
    double x, y, z;

  public:
    vector3d();
    vector3d(double x);
    vector3d(double x, double y);
    vector3d(double x, double y, double z);
    // Destruktor wird hier nicht gebraucht, da er leer bleiben würde

    /**
     * @brief Gibt den Wert der jeweiligen Komponente zurück
     *
     * @return Wert der Komponente
     */
    double get_x() const, get_y() const, get_z() const;

    /**
     * @brief Setzt den Wert für die jeweilige Komponente
     */
    void set_x(double x), set_y(double y), set_z(double z);

    /**
     * @brief Gibt den Betrag (euklidische Norm) des Vektors zurück
     */
    double abs() const;

    /**
     * @brief Gibt den Vektor multipliziert mit +1 zurück.
     */
    vector3d operator+() const;

    /**
     * @brief Gibt den Vektor multipliziert mit -1 zurück.
     */
    vector3d operator-() const;

    /**
     * @brief Gibt den Vektor als ganzes aus
     */
    void print() const;

    /**
     * @brief Addiert den Vektor auf der rechten Seite auf den Vektor der linken
     * Seite des Operators
     *
     * @param v Der zu addierende Vektor
     * @return Referenz auf diesen Vektor
     */
    vector3d &operator+=(const vector3d &v);

    /**
     * @brief Prüft die Vektoren auf Gleichheit
     *
     * @param v Der Vektor, mit dem verglichen wird
     * @return Bool mit der Info, ob Vektoren gleich waren
     */
    bool operator==(const vector3d &v) const;
};

/**
 * @brief Nimmt einen Input vom user um die Vektorkomponenten neu zu setzen
 *
 * @param is Input stream, der gelesen wird
 * @param v Der zu verändernde Vektor
 * @return Referenz auf den input stream
 */
std::istream &operator>>(std::istream &is, vector3d &v);

/**
 * @brief Schreibt den Vektor in einen output stream.
 *
 * Gibt den Vektor in einer lesbaren Form aus, z. B. als `(x, y, z)`.
 *
 * @param os output stream, in den geschrieben wird.
 * @param v Vektor, der ausgegeben werden soll.
 * @return Referenz auf den output stream.
 */
std::ostream &operator<<(std::ostream &os, const vector3d &v);

/**
 * @brief Implementiert Addition zweier Vektoren komponentenweise
 */
vector3d operator+(const vector3d &v, const vector3d &w);

/**
 * @brief Implementiert Subtraktion zweier Vektoren komponentenweise
 */
vector3d operator-(const vector3d &v, const vector3d &w);

/**
 * @brief Implementiert Multiplikation zweier Vektoren komponentenweise
 */
vector3d operator*(const vector3d &v, const vector3d &w);

product_proxy operator%(const vector3d &v, const vector3d &w);

/**
 * @class product_proxy
 * @brief Proxy class um % für vector3d mit dem Skalarprodukt und
 * dem Kreuzprodukt zu überladen
 *
 */
class product_proxy {
  private:
    // Kopien statt Referenzen um Fälle wie
    // auto p = vector3d{1, 2, 3} % vector3d{4, 5, 6};
    // abzudecken
    const vector3d v;
    const vector3d w;

  public:
    product_proxy(const vector3d &v, const vector3d &w);

    /**
     * @brief double cast overload, welcher das Skalarprodukt zurückgibt
     */
    operator double() const;

    /**
     * @brief vector3d cast overload, welcher das Kreuzprodukt zurückgibt
     */
    operator vector3d() const;
};
