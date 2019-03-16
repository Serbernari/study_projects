#ifndef GLVIEW_HPP
#define GLVIEW_HPP

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include <vector>
#include <cmath>
#include <iostream>

float CubicHermite (float A, float B, float C, float D, float x);

class glView : public QGLWidget
{
public:
    glView();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    float mTransformations(); //summing up rescaling
    void lateUpdate();
    GLuint texture;
    void LoadGLTextures( const char *name );


private:
    unsigned int calculatedPoints = 1;


    std::vector<QPoint> dotBuf; //user's points
    std::vector<QPoint> dotDrawingBuf; //points of spline

    QPoint mPosition; //mouse pos
    QTimer mTimer;

    bool UpdateOn = false;
    double mWindowScale = 1.0; //scaling
    float mShiftX = 0; //moving by wasd
    float mShiftY = 0; //moving by wasd
    float mScaleFactorX; //window resizing
    float mScaleFactorY; //window resizing
    void extendPoints(const int mul);
};

#endif // GLVIEW_HPP
