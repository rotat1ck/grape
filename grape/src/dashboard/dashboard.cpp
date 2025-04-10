#include "dashboard.h"
#include "ui_dashboard.h"
#include <QScrollBar>
#include <QVBoxLayout>
#include <algorithm>

Dashboard::Dashboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dashboard)
    , position(0)
    , step(2)
    , remainingSeconds(0)
    , isTimerRunning(false)
    , isDialogOpen(false)
{
    ui->setupUi(this);

    // Настройка бегущего текста
    movingTextBrowser = new QTextBrowser(ui->AueWordsBox);
    movingTextBrowser->setHtml("<p style='font-family: \"Julius Sans One\"; font-size: 24px; color: #000; white-space: nowrap; margin: 0;'>Если Вам холодно - встаньте в угол. Там 90`</p>");
    movingTextBrowser->setFrameStyle(QFrame::NoFrame);
    movingTextBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    movingTextBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // размеры
    movingTextBrowser->document()->setTextWidth(2000); //  ширина для текста в одну строку
    int textWidth = movingTextBrowser->document()->idealWidth();
    movingTextBrowser->setFixedSize(textWidth, 27);
    movingTextBrowser->move(0, 25);

    // таймер для анимации текста
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dashboard::updateTextPosition);
    timer->start(30); // обновление каждые 30мс

    // Создаем меню настроек
    settingsMenu = new SettingsMenu(this);

    // Настройка таймера обратного отсчета
    setupCountdownTimer();

    // Настройка дедлайнов
    setupDeadlinesBox();
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

void Dashboard::updateTextPosition()
{
    //  границы движения
    int rightBound = width();

    position += step;

    // сбрасываем позицию
    if (position > rightBound) {
        position = -movingTextBrowser->width();
    }

    movingTextBrowser->move(position, 25); // обновляем позицию
}

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

void Dashboard::updateDeadlinesList()
{
    QString content = "<div style='font-family: \"Julius Sans One\"; padding: 10px;'>";
    
    if (deadlines.isEmpty()) {
        content += "<div style='text-align: center; color: #FFFFFF; font-size: 16px; margin-top: 20px;'>"
                  "Нет активных дедлайнов</div>";
    } else {
        for (const Deadline& deadline : deadlines) {
            QDate today = QDate::currentDate();
            int daysLeft = today.daysTo(deadline.date);
            
            QString backgroundColor = "#E8D5D5";  // Базовый цвет (более 3 дней)
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
            
            content += QString(
                "<div style='margin-bottom: 15px; padding: 15px; "
                "background-color: %1; color: %2; border: 2px solid %3; "
                "border-radius: 10px; box-shadow: 0 2px 5px rgba(0,0,0,0.1);'>"
                "<div style='display: flex; justify-content: space-between; align-items: center;'>"
                "<div style='flex-grow: 1;'>"
                "<div style='font-size: 16px; color: %5;'>%4 - %6</div>"
                "</div>"
                "<div style='text-align: right; padding-left: 15px;'>"
                "<div style='font-size: 16px; font-weight: bold;'>%7</div>"
                "</div>"
                "</div>"
                "</div>"
            )
            .arg(backgroundColor)
            .arg(textColor)
            .arg(borderColor)
            .arg(deadline.name)
            .arg(accentColor)
            .arg(deadline.date.toString("dd.MM.yyyy"))
            .arg(daysLeftText);
        }
    }
    
    content += "</div>";
    ui->DeadlinesBox->setHtml(content);
}
