#include "dashboard.h"
#include "ui_dashboard.h"
#include <QScrollBar>
#include <QVBoxLayout>
#include <algorithm>

#include "../adddeadlinedialog/adddeadlinedialog.h"

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
    
    auewordsInit();
}

Dashboard::~Dashboard()
{
    delete ui;
    delete settingsMenu;
    delete countdownTimer;
}

void Dashboard::setupCountdownTimer()
{
    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &Dashboard::updateCountdownTimer);
    updateTimerDisplay();
}

void Dashboard::updateTimerDisplay()
{
    int hours = remainingSeconds / 3600;
    int minutes = (remainingSeconds % 3600) / 60;
    int seconds = remainingSeconds % 60;
    ui->timerDisplay->setText(QString("%1:%2:%3")
        .arg(hours, 2, 10, QChar('0'))
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0')));
}

void Dashboard::updateCountdownTimer()
{
    if (remainingSeconds > 0) {
        remainingSeconds--;
        updateTimerDisplay();
    } else {
        countdownTimer->stop();
        isTimerRunning = false;
        ui->timerPlayButton->setText("▶");
    }
}

void Dashboard::on_timerPlayButton_clicked()
{
    if (isTimerRunning) {
        countdownTimer->stop();
        ui->timerPlayButton->setText("▶");
    } else {
        if (remainingSeconds > 0) {
            countdownTimer->start(1000);
            ui->timerPlayButton->setText("||");
        }
    }
    isTimerRunning = !isTimerRunning;
}

void Dashboard::on_timerResetButton_clicked()
{
    countdownTimer->stop();
    isTimerRunning = false;
    remainingSeconds = 0;
    ui->timerPlayButton->setText("▶");
    updateTimerDisplay();
}

void Dashboard::on_timerPlusButton_clicked()
{
    // Добавляем время только если таймер не запущен
    if (!isTimerRunning) {
        // Добавляем 15 минут (900 секунд)
        remainingSeconds += 900;
        updateTimerDisplay();
    }
}

void Dashboard::on_timerMinusButton_clicked()
{
    // Вычитаем время только если таймер не запущен
    if (!isTimerRunning) {
        // Вычитаем 15 минут (900 секунд), но не меньше 0
        remainingSeconds = qMax(0, remainingSeconds - 900);
        updateTimerDisplay();
    }
}

// void Dashboard::on_menuSettings_clicked()
// {

void Dashboard::on_menuSettings_clicked()
{
    // Получаем позицию кнопки относительно окна Dashboard
    QPoint buttonPos = ui->menuSettings->mapToGlobal(QPoint(-74, 84));

    // Позиционируем меню
    settingsMenu->move(buttonPos.x() + ui->menuSettings->width() + 5, buttonPos.y());
    settingsMenu->show();
}

void Dashboard::setupDeadlinesBox()
{
    ui->DeadlinesBox->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->DeadlinesBox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Dashboard::on_addDeadlineButton_clicked()
{
    static bool isProcessing = false;
    if (isProcessing) {
        return;
    }
    
    isProcessing = true;
    
    AddDeadlineDialog* dialog = new AddDeadlineDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    
    connect(dialog, &QDialog::finished, this, [this, dialog](int result) {
        if (result == QDialog::Accepted) {
            Deadline newDeadline;
            newDeadline.name = dialog->getDeadlineName();
            newDeadline.date = dialog->getDeadlineDate();
            
            deadlines.append(newDeadline);
            std::sort(deadlines.begin(), deadlines.end());
            updateDeadlinesList();
        }
        isProcessing = false;
    });
    
    dialog->show();
}

void Dashboard::updateDeadlinesList() {
    qDebug() << "entered";
    if (deadlineLayout) {
        QLayoutItem* item;
        while ((item = deadlineLayout->takeAt(0))) {
            delete item->widget();
            delete item;
        }
    }
    qDebug() << "deleted";

    for (const Deadline& deadline : deadlines) {
        QDate today = QDate::currentDate();
        int daysLeft = today.daysTo(deadline.date);

        QString backgroundColor = "#D9D9D9";  // Базовый цвет (более 3 дней)
        QString textColor = "#6D5959";        // Тёмно-серый для текста
        QString borderColor = "#D4C1C1";      // Светло-розовый для рамки
        QString accentColor = "#8B7E7E";      // Акцентный цвет для даты

        if (daysLeft < 0) {
            backgroundColor = "#FFE6E6";  // Просрочено
            borderColor = "#FFCCCC";
            accentColor = "#CC7777";
        } else if (daysLeft == 1) {
            backgroundColor = "#FFE6E6";  // 1 день
            borderColor = "#FFD6D6";
            accentColor = "#CC8888";
        } else if (daysLeft == 2) {
            backgroundColor = "#FFECD9";  // 2 дня
            borderColor = "#FFE0C2";
            accentColor = "#CCA088";
        } else if (daysLeft == 3) {
            backgroundColor = "#FFF2E6";  // 3 дня
            borderColor = "#FFE6D1";
            accentColor = "#CCB088";
        }

        QString daysLeftText = daysLeft < 0 ?
                             "Просрочено" :
                             (daysLeft == 0 ? "Сегодня" :
                              QString("%1 %2").arg(daysLeft)
                                            .arg(daysLeft == 1 ? "день" :
                                                 (daysLeft < 5 ? "дня" : "дней")));

        qDebug() << "calcalated";
        QString deadlineItemStyleSheet =
            "font-size: 20px;"
            "background-color: " + backgroundColor + ";"
            "font-family: Comfortaa;"
        ;

        QWidget* deadlineItem = new QWidget(this);
        QHBoxLayout* layout = new QHBoxLayout(deadlineItem); // Create a layout for the deadlineItem
        deadlineItem->setStyleSheet(deadlineItemStyleSheet);

        QLabel* deadlineItemText = new QLabel(deadline.name, deadlineItem);
        deadlineItemText->setAlignment(Qt::AlignLeft);


        QLabel* deadlineItemDate = new QLabel(daysLeftText, deadlineItem);
        deadlineItemDate->setAlignment(Qt::AlignRight);

        layout->addWidget(deadlineItemText); // Add the name label to the layout
        layout->addWidget(deadlineItemDate);  // Add the date label to the layout

        deadlineItem->setLayout(layout); // Set the layout to the deadlineItem

        deadlineLayout->addWidget(deadlineItem);
        qDebug() << "added";
    }
}
