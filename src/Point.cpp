#include "Point.h"

/**
 * @file Point.cpp
 * @brief Implementation of the Point class used to represent 2D points.
 *
 * This file contains the definitions of the member functions of the Point class,
 * which encapsulates a 2-dimensional point defined by x and y coordinates.
 */

/**
 * @brief Default constructor.
 * 
 * Initializes a point with coordinates (0.0, 0.0).
 */
Point::Point() : x(0.0), y(0.0) {}

/**
 * @brief Parameterized constructor.
 * 
 * Initializes a point with specified x and y coordinates.
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 */
Point::Point(double x, double y) : x(x), y(y) {}

/**
 * @brief Get the coordinates of the point.
 * 
 * Returns a pointer to an array containing the x and y coordinates.
 * This array is dynamically allocated and should be deleted by the caller.
 * @return A pointer to a dynamically allocated array of two doubles.
 */
double* Point::getcoordinates() const {
    double* coords = new double[2];  // Allocate array for coordinates
    coords[0] = x;                  // Set x-coordinate
    coords[1] = y;                  // Set y-coordinate
    return coords;
}
