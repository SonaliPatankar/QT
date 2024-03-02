
#include "TriangleWindow.h"
#include <QScreen>
#include "Triangulation.h"
#include "Point3D.h"
#include "STLReader.h"
#include "Writer.h"
#include <random>
//! [3]
static const char* vertexShaderSource =
"attribute highp vec4 posAttr;\n"
"attribute lowp vec4 colAttr;\n"
"varying lowp vec4 col;\n"
"uniform highp mat4 matrix;\n"
"void main() {\n"
"   col = colAttr;\n"
"   gl_Position = matrix * posAttr;\n"
"}\n";

static const char* fragmentShaderSource =
"varying lowp vec4 col;\n"
"void main() {\n"
"   gl_FragColor = col;\n"
"}\n";
//! [3]

//! [4]
void Geometry::TriangleWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = m_program->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = m_program->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
    glEnable(GL_DEPTH_TEST);
}
//! [4]

//! [5]
void Geometry::TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -102);
    matrix.scale(0.5f);
    matrix.rotate(50.0f * m_frame / screen()->refreshRate(), 1, 0, 0);
    matrix.rotate(50.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    matrix.rotate(50.0f * m_frame / screen()->refreshRate(), 0, 0, 1);

    m_program->setUniformValue(m_matrixUniform, matrix);


    Geometry::STLReader stlReader;
    string filePath = "Sphere.stl";

    Geometry::Triangulation triangulationObj;
    stlReader.readSTL(filePath, triangulationObj);

    Geometry::Writer writer;
    vector<double> vertices = writer.write(triangulationObj);

    std::random_device random;
    std::mt19937 generate(random());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    GLfloat* colors = new GLfloat[vertices.size()];
    for (int i = 0; i < vertices.size(); ++i)
    {
        colors[i] = distribution(generate);
    }

    glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, vertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size()/3);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);

    m_program->release();

    ++m_frame;
}
//! [5]