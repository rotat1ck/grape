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

