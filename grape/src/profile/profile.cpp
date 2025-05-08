#include "ui_profile.h"
#include "profile.h"

Profile::Profile(QWidget *parent, Net* netHandler)
    : QWidget(parent),
    netHandler(netHandler),
    ui(new Ui::Profile)
{
     ui->setupUi(this);
    setupUI();
    loadUserData();
}

Profile::~Profile()
{
    delete ui;
}

//тип инитs
void Profile::loadUserData()
{

}

void Profile::setupUI()
{

}

void Profile::updateDeadlinesDisplay() {

}
