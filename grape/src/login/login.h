#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include "../../misc/clickQLabel.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_PasswordStateButton_clicked();

private:
    Ui::Login *ui;
    bool isPasswordVisible = false;
};

#endif // LOGIN_H
