#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent, Net* netHandler)
    : QWidget(parent), netHandler(netHandler),
    ui(new Ui::Login)
{
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

void Login::tryLogin() {
    QString username = ui->UsernameInput->text();
    QString password = ui->PasswordInput->text();

    Net::Result result = netHandler->user->sendLoginRequest(username, password);

    if(result.isFailure) {
        QMessageBox::critical(this, "Login error",
                              QString("Error code: %1\n%2").arg(result.status).arg(QString::fromStdString(result.message)));
    } else {
        // очистка полей после логина
        ui->UsernameInput->clear();
        ui->PasswordInput->clear();

        // = = = = = = =
        // СЮДА НАДО ЛОГИКУ ЗАПОМИНАНИЯ ДАННЫХ,
        // ЧТОБ ПРИ СЛЕДУЮЩЕМ ЗАПУСКЕ ЛОГИНИЛОСЬ САМО
        // = = = = = = =

        emit S_ChangeForm(2);
    }
}

void Login::on_LoginButton_clicked() {
    tryLogin();
}


void Login::on_PasswordInput_returnPressed() {
    tryLogin();
}

