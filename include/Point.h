#ifndef POINT_H
#define POINT_H

class Point {
public:
    double x, y;  // Coordinates of the point

    Point();      // Default constructor
    Point(double x, double y);  // Constructor to initialize the point

    double* getcoordinates() const;  // Method to get coordinates in format required by ANN, marked const
};

#endif // POINT_H
