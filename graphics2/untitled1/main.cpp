#include "mainwindow.h"
#include <QApplication>
#include "glview.hpp"

//#pragma comment (lib, "opengl32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
  //  MainWindow w;
  // w.show();
    glView win;
    win.resize(1280, 720);
    win.move(100,100);
    win.show();

    return a.exec();
}
