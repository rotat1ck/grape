#include "dashboard.h"
#include "ui_dashboard.h"
#include <QScrollBar>
#include <QVBoxLayout>
#include <algorithm>

#include "../adddeadlinedialog/adddeadlinedialog.h"
#include "../addtasks/addtask.h"

Dashboard::Dashboard(QWidget *parent, Net* netHandler)
    : QWidget(parent), netHandler(netHandler)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    // Создаем меню настроек
    deadlineLayout = new QVBoxLayout(ui->DeadlinesBoxContents);
    settingsMenu = new SettingsMenu(this);

    // Настройка таймера обратного отсчета
    setupCountdownTimer();

    // Настройка дедлайнов
    setupDeadlinesBox();
    
    // Ауе цитаты
    auewordsInit();

    // Таски
    setupTasksUI();

    // =======
    // ТЕСТОВЫЙ КОД, УДАЛИТЬ
    // =======

    netHandler->tasks->addUserTask("GOIDA");

    std::vector<Task> tasks = netHandler->tasks->getUserTasks();
    for (int i = 0; i < tasks.size(); ++i) {
        qDebug() << i << ". " + tasks[i].name;
    }

    netHandler->tasks->deleteUserTask(tasks[tasks.size() - 1].id);

    tasks = netHandler->tasks->getUserTasks();
    for (int i = 0; i < tasks.size(); ++i) {
        qDebug() << i << ". " + tasks[i].name;
    }
}

Dashboard::~Dashboard()
{
    delete ui;
    delete settingsMenu;
    delete countdownTimer;
}

