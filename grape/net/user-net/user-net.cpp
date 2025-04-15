#include "../base-net/net.h"

bool User::sendLoginRequest(QString usernameEntry, QString passwordEntry) {
    std::string username = usernameEntry.toUtf8().toStdString();
    std::string password = passwordEntry.toUtf8().toStdString();

    username = "username=" + username;
    password = "password=" + netHandler->getHashed(password);
    std::string endpoint = "/api/users/login?" + username + "&" + password;

    if (auto res = netHandler->cl->Get(endpoint)) {
        if (res->status != 200) {
            return false;
        } else {
            json response = json::parse(res->body);
            netHandler->token = response["token"];
            return true;
        }
    } else {
        std::cout << "Request error";
        return false;
    }
}
