#ifndef POINT_H
#define POINT_H

class point {
private:
    double x;
    double y;
public:
    point();
    point(double, double);
    virtual ~point();
    virtual void print() const;
    double get_x() const;
    double get_y() const;
    void input(double, double);
};

#endif
