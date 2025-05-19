#include "dashboard.h"
#include "ui_dashboard.h"
#include <QScrollBar>
void Dashboard::auewordsInit(){
    position = 0;
    step = 2;

    // Настройка бегущего текста
    movingTextBrowser = new QTextBrowser(ui->AueWordsBox);
    movingTextBrowser->setFrameStyle(QFrame::NoFrame);
    movingTextBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    movingTextBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // установка текста
    QString auetext = netHandler->user->getAUEPhase();
    setText(auetext);

    // таймер для анимации текста
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dashboard::updateTextPosition);
    timer->start(30); // обновление каждые 30мс

    QThread* thread = QThread::create([this]() {
        autoUpdateText();
    });
    thread->start();
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

void Dashboard::autoUpdateText() {
    while (true) {
        QThread::sleep(300);
        QString auetext = netHandler->user->getAUEPhase();
        emit S_AueSetText(auetext);
    }
}

void Dashboard::setText(QString text) {
    movingTextBrowser->setHtml(QString("<p style='font-family: \"Comfortaa\"; font-size: 24px; color: #000; white-space: nowrap; margin: 0;'>%1</p>").arg(text));
    movingTextBrowser->document()->setTextWidth(1000000); // ширина для текста в одну строку
    int textWidth = movingTextBrowser->document()->idealWidth();
    movingTextBrowser->setFixedSize(textWidth, 27);
    movingTextBrowser->move(0, 25);
}
