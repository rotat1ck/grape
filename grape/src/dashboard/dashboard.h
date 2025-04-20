#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QTime>
#include <QDate>

#include "../settingsmenu/settingsmenu.h"
#include "../types/structs.h"

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
    void updateTextPosition();
    void on_menuSettings_clicked();
    void on_timerPlayButton_clicked();
    void on_timerResetButton_clicked();
    void on_timerPlusButton_clicked();
    void on_timerMinusButton_clicked();
    void on_addDeadlineButton_clicked();

    void auewordsInit();


private:
    Ui::Dashboard *ui;
    QTextBrowser *movingTextBrowser;
    QTimer *timer;
    int position;
    int step;

    SettingsMenu *settingsMenu;

    QTimer *countdownTimer;
    int remainingSeconds;
    bool isTimerRunning;

    QList<Deadline> deadlines;
    QVBoxLayout* deadlineLayout;
    bool isDialogOpen;

    void setupCountdownTimer();
    void updateTimerDisplay();
    void updateCountdownTimer();
    void setupDeadlinesBox();
    void updateDeadlinesList();
};

#endif
