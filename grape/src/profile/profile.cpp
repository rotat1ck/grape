#include "ui_profile.h"
#include "profile.h"

#include <QWidget>
#include <QDate>
#include <vector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>

#include "../../net/base-net/net.h"
#include "../types/structs.h"

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
