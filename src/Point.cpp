#include "Point.h"

Point::Point(double x, double y)
{
    this->Setx(x);
    this->Sety(y);
}

Point::~Point(){}

Point::Point(const Point& other)
{
    this->Setx(other.Getx());
    this->Sety(other.Gety());
}

Point& Point::operator=(const Point& rhs)
{
    if (this == &rhs) return *this;
    //assignment operator
    return *this;
}
