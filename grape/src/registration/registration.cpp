#include "registration.h"
#include "ui_registration.h"

#include "../../misc/clickQLabel.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QTimer>

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
    connect(ui->LoginButton, &QPushButton::clicked, this, &Registration::on_RegisterButton_clicked);
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

void Registration::on_RegisterButton_clicked()
{
    QString username = ui->UsernameInput->text();
    QString email = ui->EmailInput->text();
    QString password = ui->PasswordInput->text();
    QString repeatPassword = ui->RepeatPasswordInput->text();

    if(email.isEmpty() || username.isEmpty() || password.isEmpty() || repeatPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "All fields must be filled in");
        return;
    }

    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
        if(!emailRegex.match(email).hasMatch()) {
            QMessageBox::warning(this, "Error", "Enter the correct email address");
            return;
        }

    if(password != repeatPassword) {
        QMessageBox::warning(this, "Error", "Passwords don't match");
        return;
    }

    if(password.length() < 8) {
        QMessageBox::warning(this, "Error", "The password must contain at least 8 characters");
        return;
    }

    Net::Result result = netHandler->user->sendRegisterRequest(email, username, password);

    if(result.isFailure) {
        QMessageBox::critical(this, "Error of registration",
                              QString("Error code: %1\n%2").arg(result.status).arg(QString::fromStdString(result.message)));
    } else {
        QMessageBox::information(this, "Success", "Registration was successful!");
        // очистка полей после рег
        ui->EmailInput->clear();
        ui->UsernameInput->clear();
        ui->PasswordInput->clear();
        ui->RepeatPasswordInput->clear();

        // задержка 1 сек перед переходом
        QTimer::singleShot(1000, this, [this]() {
            emit S_ChangeForm(0);
        });
    }

}

