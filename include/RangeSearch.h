#ifndef RANGESEARCH_H
#define RANGESEARCH_H

#include <vector>
#include <ANN/ANN.h>  // Include ANN library headers
#include "Point.h"     // Include the Point class header

class RangeSearch {
private:
    ANNpointArray dataPts;   // Data points array
    ANNkd_tree* kdTree;      // Pointer to kd-tree
    int pointCount;          // Number of data points

    void calboundingbox(const std::vector<Point>& polygon, ANNpoint& minPt, ANNpoint& maxPt);

public:
    RangeSearch(const std::vector<Point>& points);
    ~RangeSearch();

    bool pointinsidebox(const Point& pt, const Point& bbMin, const Point& bbMax);
    bool pointinsidepoly(const Point& pt, const std::vector<Point>& polygon);
    int queryPolyCount(const std::vector<Point>& polygon);
    std::vector<int> queryPoly(const std::vector<Point>& polygon);
};

#endif // RANGESEARCH_H
