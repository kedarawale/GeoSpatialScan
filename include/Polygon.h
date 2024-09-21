// Polygon.h
#ifndef POLYGON_H
#define POLYGON_H

#include "Point.h"

class Polygon {
public:
    Point* vertices;
    int m; // Number of vertices

    Polygon(Point* vertices, int m);
    ~Polygon();
    bool ContainsPoint(const Point& p) const; // Implement polygon point containment here
};

#endif
