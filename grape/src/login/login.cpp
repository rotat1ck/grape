#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) : QWidget(parent) , ui(new Ui::Login) {
    ui->setupUi(this);

    QIcon icon;
    icon.addFile(":/img/password.svg",QSize(34,20),QIcon::Normal,QIcon::On);
    ui->PasswordStateButton->setIcon(icon);

    ClickQLabel* registrationButton = new ClickQLabel(ui->centralwidget);
    registrationButton->setText("Register");
    registrationButton->setGeometry(390, 590, 80, 30);

    connect(registrationButton, &ClickQLabel::clicked, this, [this](){
        emit S_ChangeForm(1);
    });
}

Login::~Login()
{
    delete ui;
}

void Login::on_PasswordStateButton_clicked() {
    isPasswordVisible = !isPasswordVisible;
    if (isPasswordVisible) {
        ui->PasswordInput->setEchoMode(QLineEdit::Normal);
    } else {
        ui->PasswordInput->setEchoMode(QLineEdit::Password);
    }
}


void Login::on_LoginButton_clicked() {
    emit S_ChangeForm(2);
}

