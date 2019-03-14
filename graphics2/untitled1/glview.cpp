#include "glview.hpp"

#define WIDTH 8000
#define HEIGHT 6000
#define DENSETY 100000

float CubicHermite (float A, float B, float C, float D, float t)
{
    float a = -A/2.0f + (3.0f*B)/2.0f - (3.0f*C)/2.0f + D/2.0f;
    float b = A - (5.0f*B)/2.0f + 2.0f*C - D / 2.0f;
    float c = -A/2.0f + C/2.0f;
    float d = B;

    return a*t*t*t + b*t*t + c*t + d;
}


void glView::extendPoints(const int mul)
{
    if (dotBuf.size() >= 4)
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
    glPointSize(1);
    qglClearColor(Qt::white);
    if (calculatedPoints == 1) //cleaning only once
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    qglColor(Qt::red);
    glBegin(GL_POINTS ); //Spline  types GL_POINTS GL_LINE_STRIP
    // if (dotDrawingBuf.size() > 0)

    for(int i = 0; i < (int)dotDrawingBuf.size(); ++i)
    {
        glVertex2f(dotDrawingBuf[i].x() * mScaleFactorX + mShiftX, dotDrawingBuf[i].y() * mScaleFactorY + mShiftY);
    }
    //dotDrawingBuf.clear();

    glEnd();

    //Drawing user's points
    glPointSize(15);
    qglColor(Qt::blue);
    glBegin(GL_POINTS); // Points
    for(int i = 0; i < (int)dotBuf.size(); ++i)
    {
        glVertex2f(dotBuf[i].x()  * mScaleFactorX, dotBuf[i].y()  * mScaleFactorY);
    }
    glEnd();

    //Drawing control lines between points
    qglColor(Qt::blue);
    glBegin(GL_LINE_STRIP); // Control line
    for(int i = 0; i < (int)dotBuf.size(); ++i)
    {
        glVertex2f(dotBuf[i].x()  * mScaleFactorX, dotBuf[i].y()  * mScaleFactorY);
    }
    glEnd();
}

glView::glView()
{

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
    updateGL();
}

void glView::keyPressEvent(QKeyEvent* event)
{
    double w = 0, h = 0;
    if( event->key() == Qt::Key_W)
    {   mShiftY += 10;
        //glTranslated(0.0,-15.0,0.0);
        updateGL();
    }
    else if( event->key() == Qt::Key_A)
    {
        mShiftY -= 10;
        // glTranslated(-15.0,0.0,0.0);
        updateGL();
    }
    else if( event->key() == Qt::Key_S)
    {
       mWindowScale *= 1.1;
        updateGL();
    }
    else if( event->key() == Qt::Key_D)
    {
        mWindowScale *= 0.9;
        updateGL();
    }
}

