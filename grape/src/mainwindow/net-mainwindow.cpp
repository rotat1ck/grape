#include "mainwindow.h"

void MainWindow::setupNetHandlers() {
    netHandler = new Net();

    Net::Result res = netHandler->user->sendLoginRequest("zov@gmail.com", "testtest");
    if (!res.isFailure) {
        qDebug() << netHandler->token;
    } else {
        qDebug() << res.message;
    }

    std::vector<Task> tasks = netHandler->tasks->getUserTasks();
    for (int i = 0; i < tasks.size(); ++i) {
        qDebug() << i << ". " + tasks[i].name;
    }

    netHandler->tasks->deleteUserTask(tasks[3].id);

    tasks = netHandler->tasks->getUserTasks();
    for (int i = 0; i < tasks.size(); ++i) {
        qDebug() << i << ". " + tasks[i].name;
    }
}
