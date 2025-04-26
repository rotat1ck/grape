#include "../addtasks/addtask.h"
#include "dashboard.h"
#include "ui_dashboard.h"
#include <QScrollBar>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

// Инициализация UI для задач
void Dashboard::setupTasksUI()
{
    // Создаем layout для списка задач
    tasksLayout = new QVBoxLayout(ui->TaskBoxContents);
    tasksLayout->setAlignment(Qt::AlignTop);
    tasksLayout->setSpacing(5);

    // Кнопка добавления
    ui->addTaskButton->setCursor(Qt::PointingHandCursor);

}

// Обработчик клика на добавление
void Dashboard::on_addTaskButton_clicked()
{
    static bool isDialogOpen = false;  // Защита от повторного открытия
    if (isDialogOpen) return;

    isDialogOpen = true;

    addtask* dialog = new addtask(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    connect(dialog, &QDialog::finished, this, [=](int result) {
        isDialogOpen = false;  // Разрешаем новое открытие

        if (result == QDialog::Accepted) {
            QString taskName = dialog->taskName().trimmed();
            if (!taskName.isEmpty()) {
                addTaskToUI(taskName);
            }
        }
    });

    dialog->show();  // Используйте show() вместо exec() для немодального окна
}

// Добавление новой задачи в список
void Dashboard::addTaskToUI(const QString& taskName)
{
    QWidget* taskItem = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(taskItem);

    // Стиль задачи
    taskItem->setStyleSheet(R"(
        background: #F5F5F5;
        border-radius: 10px;
        padding: 8px;
    )");

    // Текст задачи
    QLabel* label = new QLabel(taskName);
    label->setStyleSheet(R"(
        font-family: 'Comfortaa';
        font-size: 20px;
        color: #333;
        margin-left: 5px;
    )");

    // Кнопка удаления
    QPushButton* deleteBtn = new QPushButton("×");
    deleteBtn->setStyleSheet(R"(
        color: #FF6B6B;
        font-size: 30px;
        border: none;
        background: transparent;
    )");
    deleteBtn->setCursor(Qt::PointingHandCursor);

    connect(deleteBtn, &QPushButton::clicked, [=]() {
        tasksLayout->removeWidget(taskItem);
        taskWidgets.removeOne(taskItem);
        delete taskItem;
    });

    layout->addWidget(label, 1);
    layout->addWidget(deleteBtn);
    taskItem->setLayout(layout);

    // Вставляем перед кнопкой добавления
    tasksLayout->insertWidget(tasksLayout->count() - 1, taskItem);
    taskWidgets.append(taskItem);
}
