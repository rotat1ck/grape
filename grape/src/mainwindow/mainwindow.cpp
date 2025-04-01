#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    centralWidget = new QWidget(this); // test
    setCentralWidget(centralWidget);
    layout = new QStackedLayout(centralWidget); // <- описание объекта в src/mainwindow/mainwindow.h
    centralWidget->setLayout(layout);

    login = new Login(this);

    layout->addWidget(login); /* <- таким образом добавляется объект класса
        с интерфейсом(В данном случае тип объекта Test)
        в layout, это необходимо для того чтобы layout при вызове метода setCurrentWidget
        мог отрисовать объект на экране */

    layout->setCurrentWidget(login); // <- показ виджета
}

MainWindow::~MainWindow() {
    // удаление объектов которые мы создали
    // создание с помощью new требует ручной очистки памяти
    delete layout;
    delete login;
}
