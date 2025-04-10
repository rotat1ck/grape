#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QTextBrowser>
#include <QTimer>
#include <QTime>
#include <QDate>

#include "../settingsmenu/settingsmenu.h"
#include "../adddeadlinedialog/adddeadlinedialog.h"

namespace Ui {
class Dashboard;
}

struct Deadline {
    QString name;
    QDate date;
    bool operator<(const Deadline& other) const {
        return date < other.date;
    }
};

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

    // void on_menuSettings_clicked(); // кнопка с цитатами
    void auewordsInit();
    void updateTextPosition(); // для обновления позиции текста


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
    bool isDialogOpen;

    void setupCountdownTimer();
    void updateTimerDisplay();
    void updateCountdownTimer();
    void setupDeadlinesBox();
    void updateDeadlinesList();
};

#endif
