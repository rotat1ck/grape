#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QTextBrowser>
#include <QTimer>
#include <QTime>


namespace Ui {
class Dashboard;
}

class Dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    // void on_menuSettings_clicked(); // кнопка с цитатами
    void auewordsInit();
    void updateTextPosition(); // для обновления позиции текста

private:
    Ui::Dashboard *ui;
    QTextBrowser *movingTextBrowser;
    QTimer *timer;
    int position;
    int widthWindow;
    int step;
};

#endif
