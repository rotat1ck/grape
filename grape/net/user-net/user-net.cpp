#include "../base-net/net.h"

bool User::sendLoginRequest(QString usernameEntry, QString passwordEntry) {
    username = usernameEntry.toUtf8().toStdString();
    password = passwordEntry.toUtf8().toStdString();

    std::string tempUsername = "username=" + username;
    std::string tempPassword = "password=" + netHandler->getHashed(password);

    std::string endpoint = "/api/users/login?" + tempUsername + "&" + tempPassword;
    if (auto res = netHandler->cl->Get(endpoint)) {
        if (res->status != 200) {
            return false;
        } else {
            json response = json::parse(res->body);
            emit netHandler->S_CacheToken(response["token"]);
            return true;
        }
    } else {
        return false;
    }
}

bool User::sendRegisterRequest(QString emailEntry, QString usernameEntry, QString passwordEntry) {
    std::string tempEmail = emailEntry.toUtf8().toStdString();
    username = usernameEntry.toUtf8().toStdString();
    password = passwordEntry.toUtf8().toStdString();

    tempEmail = "email=" + tempEmail;
    std::string tempUsername = "username=" + username;
    std::string tempPassword = "password=" + netHandler->getHashed(password);

    std::string endpoint = "/api/users/register?" + tempEmail + "&" + tempUsername + "&" + tempPassword;
    if (auto res = netHandler->cl->Post(endpoint)) {
        if (res->status != 200) {
            return false;
        } else {
            json response = json::parse(res->body);
            emit netHandler->S_CacheToken(response["token"]);
            return true;
        }
    } else {
        return false;
    }
}
