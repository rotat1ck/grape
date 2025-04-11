#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // исполнение кода программы переходит из main() сюда
    // подготовка основного окна
    setupViews();
    setupConnects();
    setupNetHandlers();
    defineStartWindow();
}

MainWindow::~MainWindow() {
    // удаление объектов которые мы создали
    // создание с помощью new требует ручной очистки памяти
    delete netHandler;
    delete layout;
    delete login;
    delete registration;
    delete dashboard;
}
