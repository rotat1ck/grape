#include "dashboard.h"
#include "ui_dashboard.h"
#include <QScrollBar>

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    auewordsInit();
}

Dashboard::~Dashboard()
{
    delete ui;
}

// void Dashboard::on_menuSettings_clicked()
// {

// }
