#include <stdexcept>
#include <iostream>
#include <QOpenGLShaderProgram>
#include "Writer.h"

vector<double> Geometry::Writer::write(Triangulation& triangulationObj)
{
	vector<Geometry::Point3D>& points = triangulationObj.uniquePoints();
    vector<Geometry::Triangle>& triangles = triangulationObj.triangles();
    vector<double> vertices;
    for (const Geometry::Triangle& triangle : triangles)
    {       
        vertices.push_back(points[triangle.v1()].x());
        vertices.push_back(points[triangle.v1()].y());
        vertices.push_back(points[triangle.v1()].z());

        vertices.push_back(points[triangle.v2()].x());
        vertices.push_back(points[triangle.v2()].y());
        vertices.push_back(points[triangle.v2()].z());

        vertices.push_back(points[triangle.v3()].x());
        vertices.push_back(points[triangle.v3()].y());
        vertices.push_back(points[triangle.v3()].z());
    }
    return vertices;
}