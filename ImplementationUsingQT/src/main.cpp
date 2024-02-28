// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


#include "openglwindow.h"
#include "TriangleWindow.h"
#include <QGuiApplication>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QtMath>
#include <iostream>


//! [2]
int main(int argc, char **argv)
{
    

    QGuiApplication app(argc, argv);
   
    QSurfaceFormat format;
    format.setSamples(16);

    Geometry::TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();
}
//! [2]


