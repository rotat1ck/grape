#include "../base-net/net.h"

// - - UPDATE TOKEN FUNC - -

bool User::updateToken() {
    std::string tempUsername = "username=" + username;
    std::string tempPassword = "password=" + netHandler->getHashed(password);

    std::string endpoint = "/api/users/login?" + tempUsername + "&" + tempPassword;
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

// - - LOGIN FUNCS - -

Net::Result User::sendLoginRequestImp() {
    std::string tempUsername = "username=" + username;
    std::string tempPassword = "password=" + netHandler->getHashed(password);

    std::string endpoint = "/api/users/login?" + tempUsername + "&" + tempPassword;
    if (auto res = netHandler->cl->Post(endpoint)) {
        if (res->status != 200) {
            if (res->status != 502) {
                json response = json::parse(res->body);
                return {res->status, response["error"], true};
            } else {
                return {502, "Bad gateway", true};
            }
        } else {
            json response = json::parse(res->body);
            emit netHandler->S_CacheToken(response["token"]);
            return {200, "Successful login", false};
        }
    } else {
        return {-1, "Connection failed", true};
    }
}

Net::Result User::sendLoginRequest(QString usernameEntry, QString passwordEntry) {
    username = usernameEntry.toUtf8().toStdString();
    password = passwordEntry.toUtf8().toStdString();

    return netHandler->retryRequest(3, [this]() {
        return sendLoginRequestImp();
    });
}

// - - REGISTER FUNCS - -

Net::Result User::sendRegisterRequestImp() {
    std::string tempEmail = "email=" + email;
    std::string tempUsername = "username=" + username;
    std::string tempPassword = "password=" + netHandler->getHashed(password);

    std::string endpoint = "/api/users/register?" + tempEmail + "&" + tempUsername + "&" + tempPassword;
    if (auto res = netHandler->cl->Post(endpoint)) {
        if (res->status != 200) {
            if (res->status != 502) {
                json response = json::parse(res->body);
                return {res->status, response["error"], true};
            } else {
                return {502, "Bad gateway", true};
            }
        } else {
            json response = json::parse(res->body);
            emit netHandler->S_CacheToken(response["token"]);
            return {200, "Successful login", false};
        }
    } else {
        return {-1, "Connection failed", true};
    }
}

Net::Result User::sendRegisterRequest(QString emailEntry, QString usernameEntry, QString passwordEntry) {
    email = emailEntry.toUtf8().toStdString();
    username = usernameEntry.toUtf8().toStdString();
    password = passwordEntry.toUtf8().toStdString();

    return netHandler->retryRequest(3, [this]() {
        return sendRegisterRequestImp();
    });
}
