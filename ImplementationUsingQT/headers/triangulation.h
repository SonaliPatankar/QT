#pragma once
#include "Point3D.h"
#include "Triangle.h"
#include <QDataStream>
#include <vector>
using namespace std;

namespace Geometry
{
    class Triangulation
    {
    public:
        Triangulation();
        ~Triangulation();
        vector<Triangle>& triangles();
        vector<Point3D>& uniquePoints();
        vector<Point3D>& uniqueNormals();


    private:
        vector<Triangle> mTriangles;
        vector<Point3D> mUniquePoints;
        vector<Point3D> mUniqeNormals;

    };
}