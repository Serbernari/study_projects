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
    win.show();

    return a.exec();
}
