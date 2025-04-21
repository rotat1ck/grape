#include "mainwindow.h"

void MainWindow::setupNetHandlers() {
    netHandler = new Net();

    Net::Result res = netHandler->user->sendLoginRequest("zov@gmail.com", "testtest");

    if (!res.isFailure) {
        qDebug() << netHandler->token;
    } else {
        qDebug() << res.message;
    }

    netHandler->tasks->addUserTask("GOIDA");

    std::vector<Task> tasks = netHandler->tasks->getUserTasks();
    for (int i = 0; i < tasks.size(); ++i) {
        qDebug() << i << ". " + tasks[i].name;
    }

    netHandler->tasks->deleteUserTask(tasks[tasks.size() - 1].id);

    tasks = netHandler->tasks->getUserTasks();
    for (int i = 0; i < tasks.size(); ++i) {
        qDebug() << i << ". " + tasks[i].name;
    }
}
