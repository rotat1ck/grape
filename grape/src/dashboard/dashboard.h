#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QTime>
#include <QDate>
#include <vector>

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
    //tasks
    void on_addTaskButton_clicked();



private:
    Ui::Dashboard *ui;

    // AUE
    QTextBrowser *movingTextBrowser;
    QTimer *timer;
    int position;
    int step;

    // Settings
    SettingsMenu *settingsMenu;

    // Timer
    QTimer *countdownTimer;
    int remainingSeconds;
    bool isTimerRunning;
    void setupCountdownTimer();
    void updateTimerDisplay();
    void updateCountdownTimer();

    // Deadlines
    std::vector<Deadline> deadlines;
    QVBoxLayout* deadlineLayout;
    bool isDialogOpen;
    void updateDeadlinesList();
    void setupDeadlinesBox();

    //tasks
    void setupTasksUI();
    void onAddTaskClicked();
    void addNewTask(const QString &taskName);
    void addTaskToUI(const QString& taskName);  // Добавление задачи в интерфейс
    QVBoxLayout* tasksLayout;  // Layout для списка задач
    QList<QWidget*> taskWidgets;  // Список виджетов задач

};

#endif
