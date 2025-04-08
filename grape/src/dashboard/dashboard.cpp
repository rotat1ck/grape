#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    QIcon icon;

    icon.addFile(":/img/settings.svg", QSize(218, 218), QIcon::Normal, QIcon::On);
    ui->menuSettings->setIcon(icon);
    ui->menuSettings->setIconSize(QSize(56, 56));
}

Dashboard::~Dashboard() {
    delete ui;
}

void Dashboard::on_menuSettings_clicked() {
    qDebug() << "Clicked on settings";
}

