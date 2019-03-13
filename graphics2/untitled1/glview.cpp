#include "glview.hpp"
#define WIDTH 800
#define HEIGHT 600

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

void glView::paintGL()
{
    qglClearColor(Qt::white);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    qglColor(Qt::red);

    glBegin(GL_LINE_LOOP);

    for(int i = 0; i < dotBuf.size(); ++i)
    {
        glVertex2f(dotBuf[i].x() * mScaleFactorX, dotBuf[i].y() * mScaleFactorY);
    }

    glEnd();

}

void glView::mousePressEvent(QMouseEvent* apEvent)
{
    dotBuf.push_back(apEvent->pos());
    //mPosition = apEvent->pos();
    // update();
}
