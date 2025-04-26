#include "../base-net/net.h"

// - - GETDEADLINES FUNCS - -

Net::Result Deadlines::getUserDeadlinesImp() {
    netHandler->cl->set_default_headers({{"Authorization", "Bearer " + netHandler->token}});

    std::string endpoint = "/api/deadlines/getdeadlines";
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

std::vector<Deadline> Deadlines::getUserDeadlines() {
    Net::Result res = netHandler->retryRequest(3, [this]() {
        return getUserDeadlinesImp();
    });

    if (res.isFailure == true) {
        return std::vector<Deadline> {};
    }

    json response = json::parse(res.message);
    std::vector<Deadline> deadlines;
    for (auto deadline : response["deadlines"]) {
        Deadline tmp;
        tmp.id = deadline["id"];
        tmp.name = QString::fromStdString(deadline["content"]);
        tmp.date = QDateTime::fromSecsSinceEpoch(deadline["endstamp"]).date();

        deadlines.push_back(tmp);
    }

    return deadlines;
}

// - - ADDDEADLINE FUNCS - -

Net::Result Deadlines::addUserDeadlineImp(QString content, QDate endstampEntry) {
    netHandler->cl->set_default_headers({{"Authorization", "Bearer " + netHandler->token}});

    QDateTime endstamp = QDateTime(endstampEntry, QTime(0, 0));
    QString endstampStr = QString::number(endstamp.toSecsSinceEpoch());

    std::string endpoint = "/api/deadlines/adddeadline?content=" + content.toUtf8().toStdString() + "&endstamp=" + endstampStr.toUtf8().toStdString();
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

Net::Result Deadlines::addUserDeadline(QString content, QDate endstampEntry) {
    return netHandler->retryRequest(3, [this, content, endstampEntry]() {
        return addUserDeadlineImp(content, endstampEntry);
    });
}

// - - DELETEDEADLINES FUNCS - -

Net::Result Deadlines::deleteUserDeadlineImp(int id) {
    netHandler->cl->set_default_headers({{"Authorization", "Bearer " + netHandler->token}});

    std::string endpoint = "/api/deadlines/deletedeadline/" + std::to_string(id);
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

Net::Result Deadlines::deleteUserDeadline(int id) {
    return netHandler->retryRequest(3, [this, id]() {
        return deleteUserDeadlineImp(id);
    });
}
