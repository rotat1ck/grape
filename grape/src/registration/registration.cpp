#include "registration.h"
#include "ui_registration.h"

#include "../../misc/clickQLabel.h"

Registration::Registration(QWidget *parent, Net* netHandler)
    : QWidget(parent), netHandler(netHandler)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);

    QIcon icon;
    icon.addFile(":/img/password.svg",QSize(34,20),QIcon::Normal,QIcon::On);
    ui->PasswordStateButton->setIcon(icon);
    ui->RepeatPasswordStateButton->setIcon(icon);

    ClickQLabel* loginButton = new ClickQLabel(ui->centralwidget);
    loginButton->setText("Login");
    loginButton->setGeometry(390, 660, 80, 30);

    connect(loginButton, &ClickQLabel::clicked, this, [this](){
        emit S_ChangeForm(0);
    });
}

Registration::~Registration() {
    delete ui;
}

void Registration::on_PasswordStateButton_clicked() {
    isPasswordVisible = !isPasswordVisible;
    if (isPasswordVisible) {
        ui->PasswordInput->setEchoMode(QLineEdit::Normal);
    } else {
        ui->PasswordInput->setEchoMode(QLineEdit::Password);
    }
}
void Registration::on_RepeatPasswordStateButton_clicked() {
    isRepeatPasswordVisible = !isRepeatPasswordVisible;
    if (isRepeatPasswordVisible) {
        ui->RepeatPasswordInput->setEchoMode(QLineEdit::Normal);
    } else {
        ui->RepeatPasswordInput->setEchoMode(QLineEdit::Password);
    }
}

