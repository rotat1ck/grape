#include "mainwindow.h"

void MainWindow::setupNetHandlers() {
    netHandler = new Net();

    Net::Result res = netHandler->user->sendLoginRequest("zov@gmail.com", "testtest");
    if (!res.isFailure) {
        qDebug() << netHandler->token;
    } else {
        qDebug() << res.message;
    }
}
