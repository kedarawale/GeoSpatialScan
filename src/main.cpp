// Including necessary headers and libraries

#include "RangeSearch.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <filesystem>
#include <nlohmann/json.hpp>

// Defined namespace alias for filesystem
namespace fs = std::filesystem;

/**
 * Lists all subdirectories starting with "test_case_" in the given path.
 * This function is used to find and list all test case directories.
 */

void listSubdirectories(const fs::path& path) {
    if (fs::exists(path) && fs::is_directory(path)) {
        std::cout << "Listing test case directories in: " << path << std::endl;
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_directory() && entry.path().filename().string().find("test_case_") == 0) {
                std::cout << entry.path() << std::endl;
            }
        }
    } else {
        std::cout << "The path does not exist or is not a directory." << std::endl;
    }
}

/**
 * Writes JSON data to a file with elements separated by spaces for readability.
 * This function is particularly used for arrays to format them with spaces after commas.
 * 
 * @param file Reference to the output file stream where JSON data will be written.
 * @param jsonData The JSON data to write, which can be an array or any JSON object.
 */

void writeJsonWithSpaces(std::ofstream& file, const nlohmann::json& jsonData) {
    if (jsonData.is_array()) {
        file << '[';
        for (size_t i = 0; i < jsonData.size(); ++i) {
            if (jsonData[i].is_primitive()) {
                file << jsonData[i];
            } else {
                file << jsonData[i].dump();
            }
            if (i < jsonData.size() - 1) {
                file << ", ";
            }
        }
        file << ']';
    } else {
        file << jsonData.dump();  // Fallback to normal dump for non-array types
    }
}


/**
 * Processes a single test case by reading input from JSON files, performing queries,
 * and writing the outputs to JSON files. This function handles file I/O, JSON parsing,
 * point and polygon creation, and range searching to find points within polygons.
 * 
 * @param testCasePath Filesystem path to the directory containing the test case files.
 */
void processTestCase(const fs::path& testCasePath) {
    std::string pointsJsonFilePath = (testCasePath / "input_points.json").string();
    std::string queryJsonFilePath = (testCasePath / "input_query.json").string();
    std::string outputReportJsonFilePath = (testCasePath / "output_result_report.json").string();
    std::string outputCountJsonFilePath = (testCasePath / "output_result_count.json").string();

    std::cout << "Processing test case in directory: " << testCasePath.string() << std::endl;
    auto startPreprocessing = std::chrono::high_resolution_clock::now();

    try {
        std::ifstream pointsFile(pointsJsonFilePath);
        std::ifstream queryFile(queryJsonFilePath);
        if (!pointsFile.is_open() || !queryFile.is_open()) {
            throw std::runtime_error("Cannot open JSON input files.");
        }

        nlohmann::json pointsJson = nlohmann::json::parse(pointsFile);
        nlohmann::json queryJson = nlohmann::json::parse(queryFile);
        pointsFile.close();
        queryFile.close();

        std::vector<Point> points;
        for (const auto& p : pointsJson) {
            points.emplace_back(Point{p[0].get<double>(), p[1].get<double>()});
        }

        std::vector<std::vector<Point>> polygons;
        for (const auto& poly : queryJson) {
            std::vector<Point> polygon;
            for (const auto& p : poly) {
                polygon.emplace_back(Point{p[0].get<double>(), p[1].get<double>()});
            }
            polygons.push_back(polygon);
        }

        auto endPreprocessing = std::chrono::high_resolution_clock::now();
        auto preprocessingTime = std::chrono::duration_cast<std::chrono::milliseconds>(endPreprocessing - startPreprocessing).count();

        auto startQuery = std::chrono::high_resolution_clock::now();

        RangeSearch rangeSearch(points);
        nlohmann::json outputJson = nlohmann::json::array();
        std::vector<int> counts;

        for (const auto& polygon : polygons) {
            auto insidePointsIndices = rangeSearch.queryPoly(polygon);
            outputJson.push_back(insidePointsIndices);
            counts.push_back(insidePointsIndices.size());
        }

        auto endQuery = std::chrono::high_resolution_clock::now();
        auto queryTime = std::chrono::duration_cast<std::chrono::milliseconds>(endQuery - startQuery).count();

        std::ofstream outputReportFile(outputReportJsonFilePath);
        std::ofstream outputCountFile(outputCountJsonFilePath);
        writeJsonWithSpaces(outputReportFile, outputJson);
        writeJsonWithSpaces(outputCountFile, nlohmann::json(counts));
        outputReportFile.close();
        outputCountFile.close();

        std::cout << "Preprocessing Time: " << preprocessingTime << " ms" << std::endl;
        std::cout << "Query Time: " << queryTime << " ms" << std::endl;
        std::cout << "Total Time: " << (preprocessingTime + queryTime) << " ms" << std::endl;
        if (outputReportFile && outputCountFile) {
            std::cout << "Test passed: The output files are generated" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error in " << testCasePath.string() << ": " << e.what() << std::endl;
    }
}

/**
 * Main function which initializes the application.
 */
int main() {
    fs::path path = ".";  // the path to the directory containing test cases
    listSubdirectories(path);

    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory() && entry.path().filename().string().find("test_case_") == 0) {
            processTestCase(entry.path());
        }
    }
    return 0;
}
