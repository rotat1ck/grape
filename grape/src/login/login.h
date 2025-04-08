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

signals:
    void S_ChangeForm(int formId);

private slots:
    void on_PasswordStateButton_clicked();

    void on_LoginButton_clicked();

private:
    Ui::Login *ui;
    bool isPasswordVisible = false;
};

#endif // LOGIN_H
