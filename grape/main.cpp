#include "src/mainwindow/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // <- создание приложения *вызовы методов api системы*
    MainWindow w; // <- создание объекта класса mainwindow и вызов его конструктора
    /*
        При создании объекта вызовется коструктор MainWindow::MainWindow
        Он находится в src/mainwindow/mainwindow.cpp
    */
    w.setFixedSize(400, 300); // <- установка глобального размера, для всех окон приложения
    // её использование в нашем проекте нежелательно, нужен способ автоматического скейлинга

    w.show(); // <- отрисовка окна
    return a.exec();
}
