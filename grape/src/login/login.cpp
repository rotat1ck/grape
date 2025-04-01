#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) : QWidget(parent) , ui(new Ui::Login) {
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}
