
# Implementation using QT:
This project utilizes QT Creator and OpenGL to render 3D solids. It provides functionalities for reading triangulation data from STL files, managing solid geometry, and rendering the solid in a graphical window.

# File Structure
## Point3D.h/cpp: Defines a 3D point class with x, y, and z coordinates.
Point3D(double x, double y, double z): Constructor for Point3D. 
~Point3D(): Destructor for Point3D. 
double x() const: Returns the x-coordinate of the point. 
double y() const: Returns the y-coordinate of the point. 
double z() const: Returns the z-coordinate of the point.

## Triangle.h/cpp: Represents a 3D triangle using three indices
Triangle(int v1, int v2, int v3);Constructor for Triangle 
~Triangle();Destructor for Triangle
const int v1() const; return first index 
const int v2() const; return second index 
const int v3() const; return third index

## Triangulation.h/cpp: Manages a collection of triangles forming a 3D mesh.
Triangulation(): Constructor for Triangulation. 
~Triangulation(): Destructor for Triangulation.
std::vector<Triangle>& triangles(): Return collection of triangles
std::vector<Point3D>& uniquePoints(): Return collection of unique points of solid
std::vector<Point3D>& uniqueNormals(): Return collection of normals

## STLReader.h/cpp: Read stl file and store data in triangulation object
void readSTL(const std::string& filePath, Triangulation& triangulation): Read .stl file passed though filepath and make chnages in Triangulation object which is also passed through function

## Writer.h/.cpp: Manage data of triangulation
std::vector<double> write(Triangulation& triangulationObj): Take triangulation as object and return vector of duble which holds all coordinates of a solid.

## TriangleWindow.h/cpp
void initialize() override: It's setting up the shader program, attribute locations, and enabling depth testing.
void render() override: Obtains the triangulation, writes data, generates random colors, sets attribute pointers, and draws the solid.

