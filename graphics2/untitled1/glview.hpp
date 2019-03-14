#ifndef GLVIEW_HPP
#define GLVIEW_HPP

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include <vector>
#include <cmath>

float CubicHermite (float A, float B, float C, float D, float x);

class glView : public QGLWidget
{
public:
    glView();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent*) override;

private:
    int drawnVertexes = 0;
    int calculatedPoints = 1;
    std::vector<QPoint> dotBuf;
    std::vector<QPoint> dotDrawingBuf;
    QPoint mPosition;
    QTimer mTimer;
    float mScaleFactorX;
    float mScaleFactorY;
    void extendPoints(const int mul);
};

#endif // GLVIEW_HPP
