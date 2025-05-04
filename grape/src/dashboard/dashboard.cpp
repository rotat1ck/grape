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

    // Ауе цитаты
    auewordsInit();

    // Заметки
    notesUI();
}
// функция для инициализации
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
    delete ui;
    delete settingsMenu;
    delete countdownTimer;
}

