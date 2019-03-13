#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QWidget>



class MyGLWidget : public QWidget
{
    Q_OBJECT
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
private:
    int xRot;
    int yRot;
    int zRot;
public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
public:
    explicit MyGLWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MYGLWIDGET_H
