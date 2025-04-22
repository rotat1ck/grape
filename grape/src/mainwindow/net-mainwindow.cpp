#include "mainwindow.h"

void MainWindow::setupNetHandlers() {
    netHandler = new Net();

    Net::Result res = netHandler->user->sendLoginRequest("zov@gmail.com", "testtest");

    if (!res.isFailure) {
        qDebug() << netHandler->token;
    } else {
        qDebug() << res.message;
    }

    // netHandler->tasks->addUserTask("GOIDA");

    std::vector<Task> tasks = netHandler->tasks->getUserTasks();
    for (int i = 0; i < tasks.size(); ++i) {
        qDebug() << i << ". " + tasks[i].name;
    }

    Net::Result a = netHandler->tasks->deleteUserTask(0);
    qDebug() << a.status;
    qDebug() << a.message;

    // tasks = netHandler->tasks->getUserTasks();
    // for (int i = 0; i < tasks.size(); ++i) {
    //     qDebug() << i << ". " + tasks[i].name;
    // }
}
