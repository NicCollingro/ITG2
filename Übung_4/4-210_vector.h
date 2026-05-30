// File Vector.h
#ifndef __VECTOR_H
#define __VECTOR_H

// Basisklasse vector
class vector {
	private:
		// x,y,z als alternative für dim1, dim2, dim3 weil kürzer :)
		double x;
		double y;
		double z;

		double sqr;

	public:
		// nur zwei Constructor Funktionen, eine definiert einen Vektor beliebiger Länge und Richtung, der andere einen Vektor nur mit 1
		vector(double, double, double);
		vector();
		~vector();

		void print();

		double abs();

		vector operator-();
		vector operator+();
		vector operator-(vector);
		vector operator+(vector);
		double operator*(vector); // für das Skalarprodukt
		// wird nicht funktionieren, verwende Proxy			vector operator*(vector);

		vector cross(const vector& a, const vector& b);
		
		friend vector operator*(double, vector);
