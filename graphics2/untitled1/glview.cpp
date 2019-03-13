#include "glview.hpp"

#define WIDTH 800
#define HEIGHT 600

float CubicHermite (float A, float B, float C, float D, float x)
{
    float t = x - floor(x);
    float a = -A/2.0f + (3.0f*B)/2.0f - (3.0f*C)/2.0f + D/2.0f;
    float b = A - (5.0f*B)/2.0f + 2.0f*C - D / 2.0f;
    float c = -A/2.0f + C/2.0f;
    float d = B;

    return a*t*t*t + b*t*t + c*t + d;
}


void glView::extendPoints(const int mul)
{
    if (dotBuf.size() >= 3)
    {
        for (int i = 1; i < (int)dotBuf.size(); i++)
        {
            for (int j = 0; j < mul; ++j)
            {
                printf("dot extention");
                QPoint tempDot;
                tempDot.setX(CubicHermite(dotBuf[i-1].x(), dotBuf[i].x(), dotBuf[i+1].x(), dotBuf[i+2].x(), j));
                tempDot.setY(CubicHermite(dotBuf[i-1].y(), dotBuf[i].y(), dotBuf[i+1].y(), dotBuf[i+2].y(), j));
                dotBuf_extended.push_back(tempDot);
            }
        }
    }
}

void glView::paintGL()
{
    qglClearColor(Qt::white);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    qglColor(Qt::red);
    glBegin(GL_LINE_STRIP); // types

    for(int i = 0; i < (int)dotBuf_extended.size(); ++i)
    {
      glVertex2f(dotBuf_extended[i].x() * mScaleFactorX, dotBuf[i].y() * mScaleFactorY);
    }
    glEnd();
}

glView::glView()
{
    mTimer.start(20);
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(repaint()));
}

void glView::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
}

void glView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    mScaleFactorX = WIDTH / (float)w;
    mScaleFactorY = HEIGHT / (float)h;
}

void glView::mousePressEvent(QMouseEvent* apEvent)
{
    dotBuf.push_back(apEvent->pos());
    extendPoints(100);
    //extend_dots
    //mPosition = apEvent->pos();
    // update();
}
