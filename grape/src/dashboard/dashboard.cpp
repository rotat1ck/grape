#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
}

Dashboard::~Dashboard()
{
    delete ui;
}
