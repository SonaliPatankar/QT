#include <iostream>
#include <fstream>
#include <sstream>
#include "STLReader.h"
#include <map>

void Geometry::STLReader::readSTL(const string& filePath, Triangulation& triangulation)
{
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << std::endl;
        return;
    }
    // Map to store unique points and their corresponding indices
    std::map<Geometry::Point3D, int> mappedCoordinates;
    // Read each line of the STL file
    std::string line;
    int count = 1;
    int index1;
    int index2;
    int index3;

    while (std::getline(inputFile, line))
    {
        // Check if the line contains "vertex"
        if (line.find("vertex") != std::string::npos)
        {
            // Extract x, y, z coordinates from the line
            double x;
            double y;
            double z;
            istringstream iss(line);
            string token;
            iss >> token >> x >> y >> z;

            // Create a Point3D object
            Point3D point(x, y, z);

            // Check if the point is already mapped
            auto iterator = mappedCoordinates.find(point);

            // If not mapped, add to uniquePoints and update the mapping
            if (iterator == mappedCoordinates.end())
            {
                mappedCoordinates[point] = triangulation.uniquePoints().size();
                triangulation.uniquePoints().push_back(point);
            }

            // Assign indices based on the mapping
            if (count == 1)
            {
                index1 = mappedCoordinates[point];
                count++;
            }
            else if (count == 2)
            {
                index2 = mappedCoordinates[point];
                count++;
            }
            else if (count == 3)
            {
                index3 = mappedCoordinates[point];
                count++;
            }
        }

        // When three vertices are processed, create a triangle and reset count
        if (count == 4)
        {
            Triangle triangle(index1, index2, index3);
            triangulation.triangles().push_back(triangle);
            count = 1;
        }
    }
    // Close the STL file
    inputFile.close();
}