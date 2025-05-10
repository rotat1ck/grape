#include "ui_profile.h"
#include "profile.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

Profile::Profile(QWidget *parent, Net* netHandler)
    : QWidget(parent),
    netHandler(netHandler),
    ui(new Ui::Profile)
{
    ui->setupUi(this);
    setupUI();
    loadUserData();
}

Profile::~Profile()
{
    delete ui;
}

void Profile::loadUserData()
{
    try {
        QString username = QString::fromStdString(netHandler->username);
        allDeadlines = netHandler->deadlines->getUserDeadlines();
        ui->username->setText(username);

        loadCurrentDeadlines();
        loadCompletedDeadlines();
    } catch (const std::exception& e) {
        qCritical() << "Error loading user data:" << e.what();
    }
}

void Profile::setupUI()
{
    currentLayout = new QVBoxLayout(ui->currentDeadlinesScrollAreaContents);
    completedLayout = new QVBoxLayout(ui->completedDeadlinesScrollAreaContents);
}

void Profile::loadCurrentDeadlines()
{
    // инит загрузки текущих дедлайнов
    for (Deadline deadline : allDeadlines) {

    }
}

void Profile::loadCompletedDeadlines()
{
    // инит загрузки завершенных дедлайнов
    for (Deadline deadline : allDeadlines) {

    }
}

void Profile::updateDeadlinesDisplay()
{
    QLayoutItem* item;
    while ((item = currentLayout->takeAt(0))) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
    while ((item = completedLayout->takeAt(0))) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    // current
    for (const auto& deadline : currentDeadlines) {
        QWidget* deadlineWidget = new QWidget();
        QHBoxLayout* hLayout = new QHBoxLayout(deadlineWidget);

        QLabel* titleLabel = new QLabel(deadline.name);
        QLabel* dateLabel = new QLabel(deadline.date.toString("dd.MM.yyyy"));

        hLayout->addWidget(titleLabel);
        hLayout->addWidget(dateLabel);

        currentLayout->addWidget(deadlineWidget);
    }

    // completed
    for (const auto& deadline : completedDeadlines) {
        QWidget* deadlineWidget = new QWidget();
        QHBoxLayout* hLayout = new QHBoxLayout(deadlineWidget);

        QLabel* titleLabel = new QLabel(deadline.name);
        QLabel* dateLabel = new QLabel(deadline.date.toString("dd.MM.yyyy"));

        hLayout->addWidget(titleLabel);
        hLayout->addWidget(dateLabel);

        completedLayout->addWidget(deadlineWidget);
    }
}

void Profile::on_LeftSwipeButton_clicked()
{
    emit S_ChangeForm(2);
    close();
}
