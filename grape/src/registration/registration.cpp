#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}
