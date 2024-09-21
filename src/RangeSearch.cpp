// Including necessary headers and libraries

#include "RangeSearch.h"
#include <iostream>
#include <cfloat> 
#include <vector>
#include <ANN/ANN.h>  

/**
 * Constructs a RangeSearch object that initializes a kd-tree from a list of points.
 * Each point's coordinates are copied into a dynamically allocated array suitable for ANN operations.
 *
 * @param points Vector of Point objects that represent the dataset over which queries will be performed.
 */
RangeSearch::RangeSearch(const std::vector<Point>& points) {
    pointCount = points.size();
    dataPts = annAllocPts(pointCount, 2); // Allocate points for 2D

    for (int i = 0; i < pointCount; ++i) {
        const double* coordinates = points[i].getcoordinates();
        dataPts[i][0] = coordinates[0];
        dataPts[i][1] = coordinates[1];
        delete[] coordinates; 
    }

    kdTree = new ANNkd_tree(dataPts, pointCount, 2); // Create kd-tree
  
}

/**
 * Destructor that cleans up the kd-tree and associated point data.
 */
RangeSearch::~RangeSearch() {
    delete kdTree; 
    annDeallocPts(dataPts); 
    annClose(); 
}


/**
 * Calculates the axis-aligned bounding box for a given polygon.
 *
 * @param polygon Vector of points defining the polygon.
 * @param minPt Output parameter that will hold the minimum coordinates of the bounding box.
 * @param maxPt Output parameter that will hold the maximum coordinates of the bounding box.
 */
void RangeSearch::calboundingbox(const std::vector<Point>& polygon, ANNpoint& minPt, ANNpoint& maxPt) {
    double minX = DBL_MAX, minY = DBL_MAX;
    double maxX = -DBL_MAX, maxY = -DBL_MAX;

    for (const auto& p : polygon) {
        minX = std::min(minX, p.x);
        maxX = std::max(maxX, p.x);
        minY = std::min(minY, p.y);
        maxY = std::max(maxY, p.y);
    }

    minPt[0] = minX; minPt[1] = minY;
    maxPt[0] = maxX; maxPt[1] = maxY;
}

/**
 * Determines if a point is inside a specified bounding box.
 *
 * @param pt The point to check.
 * @param bbMin The minimum coordinates (bottom-left corner) of the bounding box.
 * @param bbMax The maximum coordinates (top-right corner) of the bounding box.
 * @return True if the point is within the bounding box, False otherwise.
 */

bool RangeSearch::pointinsidebox(const Point& pt, const Point& bbMin, const Point& bbMax) {
    return pt.x >= bbMin.x && pt.x <= bbMax.x && pt.y >= bbMin.y && pt.y <= bbMax.y;
}

/**
 * Checks if a point is within the specified polygon using the ray-casting algorithm.
 * This function determines point inclusion by counting edge crossings from the point to infinity.
 *
 * @param pt The point to check.
 * @param polygon A vector of points defining the polygon.
 * @return True if the point is inside the polygon, False otherwise.
 */
bool RangeSearch::pointinsidepoly(const Point& pt, const std::vector<Point>& polygon) {
    int count = polygon.size();
    bool inside = false;
    for (int i = 0, j = count - 1; i < count; j = i++) {
        if (((polygon[i].y > pt.y) != (polygon[j].y > pt.y)) &&
            (pt.x < (polygon[j].x - polygon[i].x) * (pt.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x)) {
            inside = !inside;
        }
    }
    return inside;
}

/**
 * Counts the number of points within a specified polygon.
 *
 * @param polygon Vector of points defining the polygon.
 * @return The count of points inside the polygon.
 */
int RangeSearch::queryPolyCount(const std::vector<Point>& polygon) {
    ANNpoint minPt = annAllocPt(2), maxPt = annAllocPt(2);
    calboundingbox(polygon, minPt, maxPt);

    ANNpoint queryPt = annAllocPt(2);
    ANNidxArray nnIdx = new ANNidx[pointCount];
    ANNdistArray dists = new ANNdist[pointCount];

    int count = 0;
    for (int i = 0; i < pointCount; ++i) {
        queryPt[0] = dataPts[i][0];
        queryPt[1] = dataPts[i][1];
        if (pointinsidebox(Point(queryPt[0], queryPt[1]), Point(minPt[0], minPt[1]), Point(maxPt[0], maxPt[1]))) {

            Point pt(dataPts[nnIdx[0]][0], dataPts[nnIdx[0]][1]);
            if (pointinsidepoly(pt, polygon)) {
                ++count;
            }
        }
    }

    delete[] nnIdx;
    delete[] dists;
    annDeallocPt(queryPt);
    annDeallocPt(minPt);
    annDeallocPt(maxPt);
    return count;
}

/**
 * Queries the kd-tree to find indices of points within a specified polygon.
 *
 * @param polygon Vector of points defining the polygon.
 * @return A vector containing indices of points that are inside the polygon.
 */
std::vector<int> RangeSearch::queryPoly(const std::vector<Point>& polygon) {
    ANNpoint minPt = annAllocPt(2), maxPt = annAllocPt(2);
    calboundingbox(polygon, minPt, maxPt);

    
    ANNpoint queryPt = annAllocPt(2);  
    ANNidxArray nnIdx = new ANNidx[pointCount];  
    ANNdistArray dists = new ANNdist[pointCount];  

    std::vector<int> result;


    for (int i = 0; i < pointCount; ++i) {
        queryPt[0] = dataPts[i][0];
        queryPt[1] = dataPts[i][1];
        
        if (queryPt[0] >= minPt[0] && queryPt[0] <= maxPt[0] &&
            queryPt[1] >= minPt[1] && queryPt[1] <= maxPt[1]) {
            
            if (pointinsidepoly(Point(queryPt[0], queryPt[1]), polygon)) {
                result.push_back(i);
            }
        }
    }

    // Clean up
    delete[] nnIdx;
    delete[] dists;
    annDeallocPt(queryPt);
    annDeallocPt(minPt);
    annDeallocPt(maxPt);

    return result;
}