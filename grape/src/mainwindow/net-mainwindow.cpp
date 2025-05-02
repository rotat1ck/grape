#include "mainwindow.h"

void MainWindow::setupNetHandlers() {
    netHandler = new Net();

    // =======
    // ТЕСТОВЫЙ КОД, УДАЛИТЬ
    // =======

    Net::Result res = netHandler->user->sendLoginRequest("zov@gmail.com", "testtest");

    if (!res.isFailure) {
        qDebug() << netHandler->token;
    } else {
        qDebug() << res.message;
    }

    //QString aue = netHandler->user->getAUEPhase();
    //qDebug() << aue;
}
