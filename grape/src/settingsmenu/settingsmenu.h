#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <QDialog>
#include <QPainter>
#include <QPainterPath>
#include <QRegion>
#include <QShowEvent>

namespace Ui {
class SettingsMenu;
}

class SettingsMenu : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsMenu(QWidget *parent = nullptr);
    ~SettingsMenu();

protected:
    void paintEvent(QPaintEvent *event) override;  // Добавлено
//     void showEvent(QShowEvent *event) override;    // Добавлено
//     void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_designButton_clicked();
    void on_profileButton_clicked();
    void on_exitButton_clicked();

private:

    // void updateMask();

    Ui::SettingsMenu *ui;
};

#endif // SETTINGSMENU_H
