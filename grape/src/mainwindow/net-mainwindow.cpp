#include "mainwindow.h"

void MainWindow::setupNetHandlers() {
    netHandler = new Net();

    if (netHandler->user->sendLoginRequest("zov@gmail.com", "testtest")) {
        qDebug() << netHandler->token;
    } else {
        qDebug() << "Server said fuck you";
    }
}
