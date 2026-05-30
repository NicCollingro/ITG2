#ifndef __AREA_H
#define __AREA_H

class area{
	private:
		double a;
		point s;
	public:
		virtual void input() = 0;
		virtual void print() = 0;
		virtual double get_sx() = 0;
		virtual double get_sy() = 0;
		virtual double get_area() = 0;
};
