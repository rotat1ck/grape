#include "dashboard.h"
#include "ui_dashboard.h"
#include <QScrollBar>
#include <QVBoxLayout>
#include <algorithm>

#include "../adddeadlinedialog/adddeadlinedialog.h"
#include "../addtasks/addtask.h"

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
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

    // Заметки
    notesUI();
}

Dashboard::~Dashboard()
{
    delete ui;
    delete settingsMenu;
    delete countdownTimer;
}

