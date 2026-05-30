#include "vector3d.hpp"
#include <cmath>
#include <iostream>

// Konstruktoren
vector3d::vector3d() : x{0.0}, y{0.0}, z{0.0} {}
vector3d::vector3d(double x) : x{x}, y{x}, z{x} {}
vector3d::vector3d(double x, double y) : x{x}, y{y}, z{0.0} {}
vector3d::vector3d(double x, double y, double z) : x{x}, y{y}, z{z} {}

// Getter
double vector3d::get_x() const { return x; }
double vector3d::get_y() const { return y; }
double vector3d::get_z() const { return z; }

// Setter
void vector3d::set_x(double x) { this->x = x; }
void vector3d::set_y(double y) { this->y = y; }
void vector3d::set_z(double z) { this->z = z; }

// Mathematische Methoden
double vector3d::abs() const { return std::sqrt(x * x + y * y + z * z); }

// Unäre Operatoren
vector3d vector3d::operator+() const { return *this; }

vector3d vector3d::operator-() const { return vector3d(-x, -y, -z); }

// Eingabe
std::istream &operator>>(std::istream &is, vector3d &v) {
    double x, y, z;

    // Komponenten nur setzen, falls Zuweisung aus Input erfolgreich war
    if (is >> x >> y >> z) {
        v.set_x(x);
        v.set_y(y);
        v.set_z(z);
    }

    return is;
}

// Ausgabe
std::ostream &operator<<(std::ostream &os, const vector3d &v) {
    os << "(" << v.get_x() << ", " << v.get_y() << ", " << v.get_z() << ")";
    return os;
}

void vector3d::print() const { std::cout << *this << "\n"; }

// Binäre Operatoren
vector3d operator+(const vector3d &v, const vector3d &w) {
    return vector3d(v.get_x() + w.get_x(), v.get_y() + w.get_y(),
                    v.get_z() + w.get_z());
}

vector3d operator-(const vector3d &v, const vector3d &w) {
    return vector3d(v.get_x() - w.get_x(), v.get_y() - w.get_y(),
                    v.get_z() - w.get_z());
}

vector3d operator*(const vector3d &v, const vector3d &w) {
    return vector3d(v.get_x() * w.get_x(), v.get_y() * w.get_y(),
                    v.get_z() * w.get_z());
}

product_proxy operator%(const vector3d &v, const vector3d &w) {
    return product_proxy{v, w};
}

vector3d &vector3d::operator+=(const vector3d &v) {
    x += v.get_x();
    y += v.get_y();
    z += v.get_z();

    return *this;
}

bool vector3d::operator==(const vector3d &v) const {
    return (x == v.get_x() && y == v.get_y() && z == v.get_z());
}

// Product Proxy Methoden

product_proxy::product_proxy(const vector3d &v, const vector3d &w)
    : v{v}, w{w} {}

product_proxy::operator double() const {
    return v.get_x() * w.get_x() + v.get_y() * w.get_y() +
           v.get_z() * w.get_z();
}

product_proxy::operator vector3d() const {
    return vector3d(v.get_y() * w.get_z() - v.get_z() * w.get_y(),
                    v.get_z() * w.get_x() - v.get_x() * w.get_z(),
                    v.get_x() * w.get_y() - v.get_y() * w.get_x());
}
