#include "src/mainwindow/mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // <- создание приложения *вызовы методов api системы*
    // Загружаем шрифт из ресурсов
    QFontDatabase::addApplicationFont(":/fonts/JuliusSansOne-Regular.ttf");

    MainWindow w; // <- создание объекта класса mainwindow и вызов его конструктора
    /*
        При создании объекта вызовется коструктор MainWindow::MainWindow
        Он находится в src/mainwindow/mainwindow.cpp
    */
    // w.setFixedSize(640, 720); // <- установка глобального размера, для всех окон приложения

    w.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    w.setBaseSize(640, 720);
    w.show(); // <- отрисовка окна
    return a.exec();
}
