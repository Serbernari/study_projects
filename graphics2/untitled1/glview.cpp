#include "glview.hpp"

#define WIDTH 8000
#define HEIGHT 6000
#define DENSETY 10000
float CubicHermite (float A, float B, float C, float D, float t)
{
    float a = -A/2.0f + (3.0f*B)/2.0f - (3.0f*C)/2.0f + D/2.0f;
    float b = A - (5.0f*B)/2.0f + 2.0f*C - D / 2.0f;
    float c = -A/2.0f + C/2.0f;
    float d = B;

    float qwe = a*t*t*t + b*t*t + c*t + d;
    return qwe;
}


void glView::extendPoints(const int mul)
{
    if (dotBuf.size() > 4)
    {
        for (int i = 1; i < dotBuf.size() - 2; i++)
        {
            for (int j = 0; j < mul; ++j)
            {
                //нормализовать на 1
                float percent = ((float)j) / (float(mul - 1));
                float tx = (dotBuf.size() - 1) * percent;
                float t = tx - floor(tx);
                //j + mul * i
                QPoint tempDot;
                tempDot.setX(CubicHermite(dotBuf[i-1].x(), dotBuf[i].x(), dotBuf[i+1].x(), dotBuf[i+2].x(), t ));
                tempDot.setY(CubicHermite(dotBuf[i-1].y(), dotBuf[i].y(), dotBuf[i+1].y(), dotBuf[i+2].y(), t ));
                dotDrawingBuf.push_back(tempDot);
            }
        }
    }
}

void glView::paintGL()
{
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glPointSize(5);
    qglClearColor(Qt::white);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    qglColor(Qt::red);
    glBegin(GL_POINTS); // types GL_POINTS GL_LINE_STRIP

    if (dotDrawingBuf.size() >= 19)
    {
        for(int i = 0; i < (int)dotDrawingBuf.size(); ++i)
        {
            glVertex2f(dotDrawingBuf[i].x()  * mScaleFactorX, dotDrawingBuf[i].y()  * mScaleFactorY);
        }
    }
    glEnd();

    glPointSize(15);
    qglColor(Qt::blue);
    glBegin(GL_POINTS); // types GL_POINTS GL_LINE_STRIP
    for(int i = 0; i < (int)dotBuf.size(); ++i)
    {
        glVertex2f(dotBuf[i].x()  * mScaleFactorX, dotBuf[i].y()  * mScaleFactorY);
    }
    glEnd();
}

glView::glView()
{
    mTimer.start(20);
    // connect(&mTimer, SIGNAL(timeout()), this, SLOT(repaint()));
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
    extendPoints(DENSETY);
    //extend_dots
    //mPosition = apEvent->pos();
    updateGL();
}
