#pragma once

#include <string>
#include "Triangulation.h"

namespace Geometry
{
    class Writer
    {
    public:
        // Function to write geometry data to an STL file
        vector<double> write(Triangulation& triangulationObj);
    };
}