#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    layout = new QStackedLayout(this); // <- описание объекта в src/mainwindow/mainwindow.h

    test = new Test(this); // <- описание объекта в src/test/test.h

    layout->addWidget(test); /* <- таким образом добавляется объект класса
        с интерфейсом(В данном случае тип объекта Test)
        в layout, это необходимо для того чтобы layout при вызове метода setCurrentWidget
        мог отрисовать объект на экране */

    layout->setCurrentWidget(test); // <- показ виджета
}

MainWindow::~MainWindow() {
    // удаление объектов которые мы создали
    // создание с помощью new требует ручной очистки памяти
    delete layout;
    delete test;
}
