#include "test.h"
#include "ui_test.h"

Test::Test(QWidget *parent) : QWidget(parent) , ui(new Ui::Test) {
    ui->setupUi(this); /* <-
        Данный метод создает кодом объекты
        которые мы распологаем в .ui файле соответсвующего
        класса, можно это наглядно понять открыв файл src/test/test.ui
        он запуститься внутри редактора форм qt,
        некоторый функционал в нем недоступен поэтому
        не всегда получиться создавать интерфейс исключительно в нем
    */
}

Test::~Test() {
    delete ui;
}

void Test::on_pushButton_clicked() {
    exit(1);
}

