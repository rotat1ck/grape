#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMessageBox>

#include "../../misc/clickQLabel.h"
#include "../../net/base-net/net.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr, Net* netHandler = nullptr);
    ~Login();

signals:
    void S_ChangeForm(int formId);

private slots:
    void on_PasswordStateButton_clicked();

    void on_LoginButton_clicked();

private:
    Ui::Login *ui;
    Net* netHandler;
    bool isPasswordVisible = false;
};

#endif // LOGIN_H
