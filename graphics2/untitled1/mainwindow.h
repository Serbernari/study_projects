#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "glview.hpp"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    glView mView;
};

#endif // MAINWINDOW_H
