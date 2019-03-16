#include "glview.hpp"
#include <QFont>
#define WIDTH 8000
#define HEIGHT 6000
#define DENSETY 1500
#define SCALE_COMP 50
#define MOVE_SPEED 30

//отрисовка координатных осей
void glView::DrawAxis()
{
    int ind = 60; //расстояние меж подписями
    int len = 5;			//длина штриха
    int cenOx = WIDTH /2.0;	//центр оси по Ох
    int cenOy = HEIGHT /2.0;	//центр оси по Оу
    int lineShiftX = 14;	//сдвиг подписи с Ох
    int sepShiftX = 2;		//сдвиг подписи от линии разделения
    int lineShiftY = 7;		//сдвиг подписи с Оу
    int sepShiftY = 3;		//сдвиг подписи от линии разделения

    //нарисовать координатные подписи
    for(int i = 0; i < 100; i++)
    {
        glLineWidth(10);
        glColor3ub(255, 0, 0);
        //по Ох
        glBegin(GL_LINES);
            glVertex2i(cenOx + i*ind, cenOy - len);
            glVertex2i(cenOx + i*ind, cenOy + len);
        glEnd();
        glBegin(GL_LINES);
            glVertex2i(cenOx - i*ind, cenOy - len);
            glVertex2i(cenOx - i*ind, cenOy + len);
        glEnd();

        //по Оу
        glBegin(GL_LINES);
            glVertex2i(cenOx - len, cenOy + i*ind);
            glVertex2i(cenOx + len, cenOy + i*ind);
        glEnd();
        glBegin(GL_LINES);
            glVertex2i(cenOx - len, cenOy - i*ind);
            glVertex2i(cenOx + len, cenOy - i*ind);
        glEnd();

        //вывести подписи к координатным осям
        glColor3ub(0, 255, 0);
        char dest[10];
        double num = 10;//(double)i * mScaleFactorX;

        //преобразование числа в строку
        sprintf(dest, "%0.2lf", num);
        std::string out = std::string(dest);

        QFont f("Helvetica");

        //по оси Ох
      //  for(auto a : out)
        QPoint test;
        test.setX(100);
        test.setY(100);
        QPainter painter(this);
     painter.drawText(test,"MY FUCKING TEXT");
       // for(auto a : out)


        //по оси Оу
        if(i != 0)
        {
            //for(auto a : out)

            //for(auto a : out)

        }
    }

    //нарисовать координатные оси
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
        glVertex2i(-5, cenOy);
        glVertex2i( 5, cenOy);
    glEnd();
    glBegin(GL_LINES);
        glVertex2i(cenOx,-5);
        glVertex2i(cenOx, 5);
    glEnd();
}


void glView::LoadGLTextures( const char *name )
{
    QImage img;

    if(!img.load(name))
    {
        std::cerr << "ERROR while loading image" << std::endl;
    }

    QImage t = QGLWidget::convertToGLFormat(img);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glBindTexture( GL_TEXTURE_2D, 0 );
}

float CubicHermite (float A, float B, float C, float D, float t)
{
    float a = -A/2.0f + (3.0f*B)/2.0f - (3.0f*C)/2.0f + D/2.0f;
    float b = A - (5.0f*B)/2.0f + 2.0f*C - D / 2.0f;
    float c = -A/2.0f + C/2.0f;
    float d = B;

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
        calculatedPoints = dotBuf.size();
        for (unsigned long long i = 1; i < dotBuf.size() - 2; i++)
        {
            for (int j = 0; j < mul * myQPointDistNorm(dotBuf[i+1], dotBuf[i]) ; ++j)
            {
                //нормализовать на 1
                double percent = ((double)j) / (double(mul - 1));
                double tx = (dotBuf.size() - 1) * percent;
                double t = tx - floor(tx);
                QPoint tempDot;
                tempDot.setX((int)CubicHermite(dotBuf[i-1].x(), dotBuf[i].x(), dotBuf[i+1].x(), dotBuf[i+2].x(), t ));
                tempDot.setY((int)CubicHermite(dotBuf[i-1].y(), dotBuf[i].y(), dotBuf[i+1].y(), dotBuf[i+2].y(), t ));
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

   /* glEnable(GL_TEXTURE_2D); //texture
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 3.0f);     glVertex2f(- WIDTH,  HEIGHT);  // vertex 1
    glTexCoord2f(0.0f, 0.0f);     glVertex2f(- WIDTH, - HEIGHT); // vertex 2
    glTexCoord2f(3.0f, 0.0f);     glVertex2f( WIDTH, - HEIGHT); // vertex 3
    glTexCoord2f(3.0f, 3.0f);     glVertex2f( WIDTH,  HEIGHT); // vertex 4
    glEnd();
    glDisable(GL_TEXTURE_2D);*/

    DrawAxis();

    qglColor(Qt::red);
    glBegin(GL_POINTS); //Spline  types GL_POINTS GL_LINE_STRIP
    if (dotDrawingBuf.size() > 0)
    {
        for(unsigned long long i = 0; i < dotDrawingBuf.size(); ++i)
        {
            glVertex2f(dotDrawingBuf[i].x() * mScaleFactorX + mShiftX, dotDrawingBuf[i].y() * mScaleFactorY + mShiftY);
        }
    }
    glEnd();

    //Drawing user's points
    glPointSize(15);
    qglColor(Qt::blue);
    glBegin(GL_POINTS); // Points
    for(unsigned long long i = 0; i < dotBuf.size(); ++i)
    {
        glVertex2f(dotBuf[i].x()  * mScaleFactorX + mShiftX, dotBuf[i].y()  * mScaleFactorY + mShiftY);
    }
    glEnd();

    //Drawing control lines between points
    qglColor(Qt::blue);
    glBegin(GL_LINE_STRIP); // Control line
    for(unsigned long long i = 0; i < dotBuf.size(); ++i)
    {
        glVertex2f(dotBuf[i].x()  * mScaleFactorX + mShiftX, dotBuf[i].y()  * mScaleFactorY + mShiftY);
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
    glEnable(GL_TEXTURE_2D);
    LoadGLTextures("2.bmp");
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
        //glTranslated(0.0,-15.0,0.0);
        lateUpdate();
    }
    else if( event->key() == Qt::Key_S)
    {
        mShiftY -= MOVE_SPEED;
        // mWindowScale *= 1.1;
        lateUpdate();
    }
    else if( event->key() == Qt::Key_A)
    {
        mShiftX += MOVE_SPEED;
        // glTranslated(-15.0,0.0,0.0);
        lateUpdate();
    }
    else if( event->key() == Qt::Key_D)
    {
        mShiftX -= MOVE_SPEED;
        // mWindowScale *= 0.9;
        lateUpdate();
    }
    else if( event->key() == Qt::Key_Up)
    {

        mScaleFactorX *= 1.01;
        mShiftX -= SCALE_COMP;
        mScaleFactorY *= 1.01;
        mShiftY -= SCALE_COMP;
        lateUpdate();
    }
    else if( event->key() == Qt::Key_Down)
    {
        mScaleFactorX *= 0.99;
        mShiftX += SCALE_COMP;
        mScaleFactorY *= 0.99;
        mShiftY += SCALE_COMP;
        lateUpdate();
    }
}

