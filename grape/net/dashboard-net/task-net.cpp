#include "../base-net/net.h"

// - - GETTASKS FUNCS - -

Net::Result Tasks::getUserTasksImp() {
    netHandler->cl->set_default_headers({{"Authorization", "Bearer " + netHandler->token}});

    std::string endpoint = "/api/tasks/gettasks";
    if (auto res = netHandler->cl->Get(endpoint)) {
        if (res->status != 200) {
            if (res->status != 502) {
                json response = json::parse(res->body);
                return {res->status, response["error"], true};
            } else {
                return {502, "Bad gateway", true};
            }
        } else {
            return {200, res->body, false};
        }
    } else {
        return {-1, "Connection failed", true};
    }
}

std::vector<Task> Tasks::getUserTasks() {
    Net::Result res = netHandler->retryRequest(3, [this]() {
        return getUserTasksImp();
    });

    if (res.isFailure == true) {
        return std::vector<Task> {};
    }

    json response = json::parse(res.message);
    std::vector<Task> tasks;
    for (auto task : response["tasks"]) {
        Task tmp;
        tmp.id = task["id"];
        tmp.name = QString::fromStdString(task["content"]);
        tasks.push_back(tmp);
    }

    return tasks;
}

// - - ADDTASK FUNCS - -

Net::Result Tasks::addUserTaskImp(QString content) {
    netHandler->cl->set_default_headers({{"Authorization", "Bearer " + netHandler->token}});

    std::string endpoint = "/api/tasks/addtask?content=" + content.toUtf8().toStdString();
    if (auto res = netHandler->cl->Post(endpoint)) {
        if (res->status != 200) {
            if (res->status != 502) {
                json response = json::parse(res->body);
                return {res->status, response["error"], true};
            } else {
                return {502, "Bad gateway", true};
            }
        } else {
            return {200, "Task added", false};
        }
    } else {
        return {-1, "Connection failed", true};
    }
}

Net::Result Tasks::addUserTask(QString content) {
    return netHandler->retryRequest(3, [this, content]() {
        return addUserTaskImp(content);
    });
}

// - - DELETETASK FUNCS - -

Net::Result Tasks::deleteUserTaskImp(int id) {
    netHandler->cl->set_default_headers({{"Authorization", "Bearer " + netHandler->token}});

    std::string endpoint = "/api/tasks/deletetask/" + std::to_string(id);
    if (auto res = netHandler->cl->Delete(endpoint)) {
        if (res->status != 200) {
            if (res->status != 502) {
                json response = json::parse(res->body);
                return {res->status, response["error"], true};
            } else {
                return {502, "Bad gateway", true};
            }
        } else {
            return {200, "Task deleted", false};
        }
    } else {
        return {-1, "Connection failed", true};
    }
}

Net::Result Tasks::deleteUserTask(int id) {
    return netHandler->retryRequest(3, [this, id]() {
        return deleteUserTaskImp(id);
    });
}
