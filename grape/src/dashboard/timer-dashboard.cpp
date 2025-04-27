#include "dashboard.h"
#include "ui_dashboard.h"

void Dashboard::setupCountdownTimer()
{
    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &Dashboard::updateCountdownTimer);
    remainingSeconds = 0;
    isTimerRunning = false;
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
        isTimerRunning = !isTimerRunning;
    } else {
        if (remainingSeconds > 0) {
            countdownTimer->start(1000);
            ui->timerPlayButton->setText("||");
            isTimerRunning = !isTimerRunning;
        }
    }
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
