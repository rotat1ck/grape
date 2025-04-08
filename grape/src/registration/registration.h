#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>

namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

signals:
    void S_ChangeForm(int formId);

private slots:
    void on_PasswordStateButton_clicked();
    void on_RepeatPasswordStateButton_clicked();

private:
    Ui::Registration *ui;
    bool isPasswordVisible = false;
    bool isRepeatPasswordVisible = false;
};

#endif // REGISTRATION_H
