#include "ui_profile.h"
#include "profile.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

Profile::Profile(QWidget *parent, Net* netHandler)
    : QWidget(parent),
    netHandler(netHandler),
    ui(new Ui::Profile),

    currentDeadlinesContainer(nullptr),
    completedDeadlinesContainer(nullptr),
    currentLayout(nullptr),
    completedLayout(nullptr)
{
    ui->setupUi(this);
    setupUI();
    loadUserData();

    connect(ui->LeftSwipeButton, &QPushButton::clicked,
            this, &Profile::on_LeftSwipeButton_clicked);
}

Profile::~Profile()
{
    delete currentDeadlinesContainer;
    delete completedDeadlinesContainer;
    delete ui;
}

void Profile::loadUserData()
{
    // if (!netHandler) {
    //     qWarning() << "NetHandler is not initialized";
    //     return;
    // }

    // try {
    //     QString username = QString::fromStdString(netHandler->username);
    //     ui->username->setText(username);

    //     loadCurrentDeadlines();
    //     loadCompletedDeadlines();
    // } catch (const std::exception& e) {
    //     qCritical() << "Error loading user data:" << e.what();
    // }
}

void Profile::setupUI()
{
    // currentDeadlinesContainer = new QWidget();
    // completedDeadlinesContainer = new QWidget();

    // currentLayout = new QVBoxLayout(currentDeadlinesContainer);
    // completedLayout = new QVBoxLayout(completedDeadlinesContainer);

    // ui->currentDeadlinesScrollArea->setWidget(currentDeadlinesContainer);
    // ui->completedDeadlinesScrollArea->setWidget(completedDeadlinesContainer);

    // ui->currentDeadlinesScrollArea->setWidgetResizable(true);
    // ui->completedDeadlinesScrollArea->setWidgetResizable(true);
}

void Profile::loadCurrentDeadlines()
{
    if (!netHandler) return;

    // инит загрузки текущих дедлайнов
}

void Profile::loadCompletedDeadlines()
{
    if (!netHandler) return;

    // инит загрузки завершенных дедлайнов
}

void Profile::updateDeadlinesDisplay()
{
    // QLayoutItem* item;
    // while ((item = currentLayout->takeAt(0))) {
    //     if (item->widget()) {
    //         delete item->widget();
    //     }
    //     delete item;
    // }
    // while ((item = completedLayout->takeAt(0))) {
    //     if (item->widget()) {
    //         delete item->widget();
    //     }
    //     delete item;
    // }

    // // current
    // for (const auto& deadline : currentDeadlines) {
    //     QWidget* deadlineWidget = new QWidget();
    //     QHBoxLayout* hLayout = new QHBoxLayout(deadlineWidget);

    //     QLabel* titleLabel = new QLabel(QString::fromStdString(deadline.title));
    //     QLabel* dateLabel = new QLabel(deadline.dueDate.toString("dd.MM.yyyy"));

    //     hLayout->addWidget(titleLabel);
    //     hLayout->addWidget(dateLabel);

    //     currentLayout->addWidget(deadlineWidget);
    // }

    // // completed
    // for (const auto& deadline : completedDeadlines) {
    //     QWidget* deadlineWidget = new QWidget();
    //     QHBoxLayout* hLayout = new QHBoxLayout(deadlineWidget);

    //     QLabel* titleLabel = new QLabel(QString::fromStdString(deadline.title));
    //     QLabel* dateLabel = new QLabel(deadline.dueDate.toString("dd.MM.yyyy"));

    //     hLayout->addWidget(titleLabel);
    //     hLayout->addWidget(dateLabel);

    //     completedLayout->addWidget(deadlineWidget);
    // }
}

void Profile::on_LeftSwipeButton_clicked()
{
    emit S_ChangeForm(2);
    close();
}
