#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>

#include "../../net/base-net/net.h"

namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr, Net* netHandler = nullptr);
    ~Registration();

signals:
    void S_ChangeForm(int formId);

private slots:
    void on_PasswordStateButton_clicked();
    void on_RepeatPasswordStateButton_clicked();
    void on_RegisterButton_clicked();

private:
    Ui::Registration *ui;
    Net* netHandler;
    bool isPasswordVisible = false;
    bool isRepeatPasswordVisible = false;
};

#endif // REGISTRATION_H
