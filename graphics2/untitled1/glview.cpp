#include "glview.hpp"

#define WIDTH 8000
#define HEIGHT 6000
#define DENSETY 1500
#define SCALE_COMP 50
#define MOVE_SPEED 30

//выдавать экранные координаты
//выдавать значения сплайна
//нормальный зум
//отрисовка координатных осей

void glView::LoadGLTextures( const char *name )
{
    QImage img;

    if(!img.load(name))
    { std::cerr << "ERROR while loading image" << std::endl; }

    QImage t = QGLWidget::convertToGLFormat(img);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glBindTexture( GL_TEXTURE_2D, 0 );
}

double CubicHermite (double A, double B, double C, double D, double t)
{
    double a = -A/2.0 + (3.0*B)/2.0 - (3.0*C)/2.0 + D/2.0;
    double b = A - (5.0*B)/2.0 + 2.0*C - D / 2.0;
    double c = -A/2.0 + C/2.0;
    double d = B;

    return a*t*t*t + b*t*t + c*t + d;
}

float myQPointDistNorm (QPoint i,QPoint j)
{
    return (1 - 1/((i.x() - j.x())*(i.x() - j.x()) + (i.y() - j.y())*(i.y() - j.y())));
}

void glView::extendPoints(const int mul)
{
    if (dotBuf.size() >= 4)
    {
        if (dotBuf.size() - calculatedPoints)
        {dotDrawingBuf.clear();}
        calculatedPoints = static_cast<unsigned int>(dotBuf.size());
        for (unsigned long long i = 1; i < dotBuf.size() - 2; i++)
        {
            for (int j = 0; j < mul * myQPointDistNorm(dotBuf[i+1], dotBuf[i]) ; ++j)
            {
                //нормализовать на 1
                double percent = (static_cast<double>(j)) / (static_cast<double>((mul - 1)));
                double tx = (dotBuf.size() - 1) * percent;
                double t = tx - floor(tx);
                QPoint tempDot;
                tempDot.setX(static_cast<int>(
                                 CubicHermite(dotBuf[i-1].x(), dotBuf[i].x(),
                                 dotBuf[i+1].x(), dotBuf[i+2].x(), t )));
                tempDot.setY(static_cast<int>(
                                 CubicHermite(dotBuf[i-1].y(), dotBuf[i].y(), dotBuf[i+1].y(),
                             dotBuf[i+2].y(), t )));
                dotDrawingBuf.push_back(tempDot);
            }
        }
    }
}

void glView::paintGL()
{
    glPointSize(1);
    qglClearColor(Qt::white);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D); //texture
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 3.0f);     glVertex2f(- WIDTH,  HEIGHT);  // vertex 1 add scale factorsS делать в инициализации а не в дисплее
    glTexCoord2f(0.0f, 0.0f);     glVertex2f(- WIDTH, - HEIGHT); // vertex 2
    glTexCoord2f(3.0f, 0.0f);     glVertex2f( WIDTH, - HEIGHT); // vertex 3
    glTexCoord2f(3.0f, 3.0f);     glVertex2f( WIDTH,  HEIGHT); // vertex 4
    glEnd();
    glDisable(GL_TEXTURE_2D);

    qglColor(Qt::red);
    glBegin(GL_POINTS); //Spline  types GL_POINTS GL_LINE_STRIP
    if (dotDrawingBuf.size() > 0)
    {
        for(unsigned long long i = 0; i < dotDrawingBuf.size(); ++i)
        {
            glVertex2f(dotDrawingBuf[i].x() * static_cast<float>(mScaleFactorX) * userScaleFactor + mShiftX,
                       dotDrawingBuf[i].y() * static_cast<float>(mScaleFactorY) * userScaleFactor+ mShiftY);
        }
    }
    glEnd();

    //Drawing user's points
    glPointSize(15);
    qglColor(Qt::blue);
    glBegin(GL_POINTS); // Points
    for(unsigned long long i = 0; i < dotBuf.size(); ++i)
    {
        glVertex2f(dotBuf[i].x() * static_cast<float>(mScaleFactorX) * userScaleFactor+ mShiftX,
                   dotBuf[i].y() * static_cast<float>(mScaleFactorY) * userScaleFactor+ mShiftY);
    }
    glEnd();

    //Drawing control lines between points
    qglColor(Qt::blue);
    glBegin(GL_LINE_STRIP); // Control line
    for(unsigned long long i = 0; i < dotBuf.size(); ++i)
    {
        glVertex2f(dotBuf[i].x() * static_cast<float>(mScaleFactorX) * userScaleFactor + mShiftX, dotBuf[i].y()
                   * static_cast<float>(mScaleFactorY)* userScaleFactor + mShiftY);
    }
    glEnd();

    QString tmp = "Axis X shift: "; //не создават ькаждый раз, ну ёбана
    tmp += QString::number(mShiftX);
    glColor3f(1,0,0);
    QFont myFont("Times", 12, QFont::Bold);
    this->renderText(1100, 50, tmp, myFont);

    QString tmp2 = "Axis Y shift: ";
    tmp2 += QString::number(mShiftY);
    glColor3f(1,0,0);
    QFont myFont2("Times", 12, QFont::Bold);
    this->renderText(1100, 70, tmp2, myFont2);

}

glView::glView()
{

}

void glView::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
    glEnable(GL_TEXTURE_2D);
    LoadGLTextures("2.bmp");
}

void glView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    mScaleFactorX = ((WIDTH / static_cast<double>(w)));
    mScaleFactorY = ((HEIGHT / static_cast<double>(h)));
}

void glView::mousePressEvent(QMouseEvent* apEvent)
{
    QPoint tmpPoint;
    tmpPoint.setX((apEvent->x() - mShiftX / static_cast<int>(mScaleFactorX)));
    tmpPoint.setY((apEvent->y() - mShiftY / static_cast<int>(mScaleFactorY)));
    tmpPoint.setX(tmpPoint.x() / userScaleFactor);
    tmpPoint.setY(tmpPoint.y() / userScaleFactor);

    dotBuf.push_back(tmpPoint);
    extendPoints(DENSETY);
    updateGL();
}

void glView::lateUpdate()
{
    if (UpdateOn == false)
    {
        UpdateOn = true;
        mTimer.start(40);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(update()));
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(UpdateOn = false));
    }
}

void glView::keyPressEvent(QKeyEvent* event)
{
    if( event->key() == Qt::Key_W)
    {
        mShiftY += MOVE_SPEED;
        lateUpdate();
    }
    else if( event->key() == Qt::Key_S)
    {
        mShiftY -= MOVE_SPEED;
        lateUpdate();
    }
    else if( event->key() == Qt::Key_A)
    {
        mShiftX += MOVE_SPEED;
        lateUpdate();
    }
    else if( event->key() == Qt::Key_D)
    {
        mShiftX -= MOVE_SPEED;
        lateUpdate();
    }
    else if( event->key() == Qt::Key_Up)
    {

        userScaleFactor *= 1.01;
        //mShiftX -= SCALE_COMP;
        //mScaleFactorY *= 1.01;
        //mShiftY -= SCALE_COMP;
        lateUpdate();
    }
    else if( event->key() == Qt::Key_Down)
    {
        userScaleFactor *= 0.99;
        //mShiftX += SCALE_COMP;
        //mScaleFactorY *= 0.99;
        //mShiftY += SCALE_COMP;
        lateUpdate();
    }
}

