#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <QDialog>

namespace Ui {
class SettingsMenu;
}

class SettingsMenu : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsMenu(QWidget *parent = nullptr);
    ~SettingsMenu();

private slots:
    void on_designButton_clicked();
    void on_profileButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::SettingsMenu *ui;
};

#endif // SETTINGSMENU_H
