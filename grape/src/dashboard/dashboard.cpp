#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent, Net* netHandler)
    : QWidget(parent), netHandler(netHandler)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    // Ауе цитаты
    auewordsInit();
    connect(this, &Dashboard::S_AueSetText, this, &Dashboard::setText);

    // Заметки
    notesUI();
}

void Dashboard::initDashboard() {
    if (isInitialized) {
        return; // инициализировано - выходим
    }

    // Создаем меню настроек
    settingsMenu = new SettingsMenu(this);
    connect(settingsMenu, &SettingsMenu::S_ChangeForm, this, [&](int formId){
        emit S_ChangeForm(formId);
    });

    // Настройка таймера обратного отсчета
    setupCountdownTimer();

    // Настройка дедлайнов
    setupDeadlinesBox();

    // Таски
    setupTasksUI();

    isInitialized = true; // все оке оке заебись
}

Dashboard::~Dashboard()
{
    // Base
    delete ui;

    // AUE
    delete timer;
    delete movingTextBrowser;

    // Settings
    delete settingsMenu;

    // Timer
    delete countdownTimer;

    // Deadlines
    while (QLayoutItem* item = deadlineLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    delete deadlineLayout;

    // Tasks
    while (QLayoutItem* item = tasksLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    delete tasksLayout;
}

