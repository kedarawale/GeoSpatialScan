// Polygon.cpp
#include "Polygon.h"

/**
 * @file Polygon.cpp
 * @brief Implementation of the Polygon class used to represent 2D polygons.
 *
 * This file contains the definitions of the member functions of the Polygon class,
 * which encapsulates a 2-dimensional polygon defined by an array of Point instances
 * representing its vertices.
 */

/**
 * @brief Constructor for the Polygon class.
 * 
 * Initializes a polygon with a specified array of vertices. The number of vertices
 * is also specified to manage the geometry of the polygon.
 * @param vertices Pointer to the array of Point objects that make up the polygon's vertices.
 * @param m The number of vertices in the polygon.
 */
Polygon::Polygon(Point* vertices, int m) : vertices(vertices), m(m) {}

/**
 * @brief Destructor for the Polygon class.
 * 
 * Cleans up resources used by the Polygon instance. This implementation assumes that
 * the vertices are dynamically allocated elsewhere, and thus it does not delete the vertices array.
 * The caller must manage the memory for vertices properly.
 */
Polygon::~Polygon() {
    
}
