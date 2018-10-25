#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point();
        virtual ~Point();
        Point(const Point& other);
        Point& operator=(const Point& other);

        double Getx() { return x; }
        void Setx(double val) { x = val; }
        double Gety() { return y; }
        void Sety(double val) { y = val; }

    protected:

    private:
        double x;
        double y;
};

#endif // POINT_H
