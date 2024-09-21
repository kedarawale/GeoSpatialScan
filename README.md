# GeoSpatialScan : An Optimized Polygon Range Search Algorithm 

GeoSpatialScan is an advanced C++ implementation of an efficient spatial search algorithm that leverages KD-trees for rapid point-in-polygon queries. It utilizes the Approximate Nearest Neighbor (ANN) library to construct a KD-tree from a set of n two-dimensional points, enabling logarithmic-time spatial queries.

## Features

- KD-tree construction using ANN library
- Polygon range queries:
  - Count Query: Returns the number of points within a specified polygon
  - Report Query: Retrieves indices of all points inside the specified polygon
- Robust geometric functions (point-in-polygon test, bounding box calculations)
- Input/output in JSON format
- Automated testing setup

## What is KD tree?

A KD-tree (k-dimensional tree) is a specialized data structure for efficiently organizing and searching points in k-dimensional space. It recursively partitions the space along different dimensions, creating a binary tree where each node represents a point and a splitting hyperplane. KD-trees excel at operations like nearest neighbor search and range queries, making them valuable in various fields such as computer graphics, machine learning, and geographic information systems.

## System Requirements

- C++17 compatible compiler (GCC or Clang)
- ANN library
- nlohmann/json library (included in repo)
- Compatible with Unix-like operating systems (Linux, macOS)


## How to Compile and Run

1. Open terminal in the project folder and run the following commands : 
  - ``` make clean```
   - ``` make ```
   - ```./bin/rangesearch ```
2. The program will create an `output.json` file with the results
This file includes the results of the range search, listing the data points that lie within or on the boundary of the specified query polygon Q, according to the algorithm's design.

## Running Custom Test Scenarios

1. Upload a folder (e.g., 'test_case_01') with four JSON files:
- `input_points.json`
- `input_query.json`
- `output_count.json`
- `output_report.json`

2. After running the test, two output files will be produced:
- `output_result_count.json`
- `output_result_report.json`

Output files will be created in the same folder as the test case.
