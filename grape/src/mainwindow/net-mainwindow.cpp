#include "mainwindow.h"

void MainWindow::setupNetHandlers() {
    netHandler = new Net();

    if (netHandler->user->sendLoginRequest("test", "test")) {
        qDebug() << netHandler->token;
    } else {
        qDebug() << "Server said fuck you";
    }
}
