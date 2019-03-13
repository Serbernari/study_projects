#ifndef GLVIEW_HPP
#define GLVIEW_HPP

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include <vector>

class glView : public QGLWidget
{
public:
    glView();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent*) override;

private:
    std::vector<QPoint> dotBuf;
    QPoint mPosition;
    QTimer mTimer;
    float mScaleFactorX;
    float mScaleFactorY;
};

#endif // GLVIEW_HPP
