#include "../base-net/net.h"

// - - LOGIN FUNCS - -

Net::Result User::sendLoginRequestImp() {
    std::string tempUsername = "username=" + netHandler->username;
    std::string tempPassword = "password=" + netHandler->getHashed(netHandler->password);

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
    netHandler->username = usernameEntry.toUtf8().toStdString();
    netHandler->password = passwordEntry.toUtf8().toStdString();

    return netHandler->retryRequest(3, [this]() {
        return sendLoginRequestImp();
    });
}

// - - REGISTER FUNCS - -

Net::Result User::sendRegisterRequestImp() {
    std::string tempEmail = "email=" + netHandler->email;
    std::string tempUsername = "username=" + netHandler->username;
    std::string tempPassword = "password=" + netHandler->getHashed(netHandler->password);

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
            return {200, "Successful registrated", false};
        }
    } else {
        return {-1, "Connection failed", true};
    }
}

Net::Result User::sendRegisterRequest(QString emailEntry, QString usernameEntry, QString passwordEntry) {
    netHandler->email = emailEntry.toUtf8().toStdString();
    netHandler->username = usernameEntry.toUtf8().toStdString();
    netHandler->password = passwordEntry.toUtf8().toStdString();

    return netHandler->retryRequest(3, [this]() {
        return sendRegisterRequestImp();
    });
}

// - - AUE - -

Net::Result User::getAUEPhaseImp() {
    std::string endpoint = "/api/aue/getphase";
    if (auto res = netHandler->cl->Get(endpoint)) {
        if (res->status != 200) {
            if (res->status != 502) {
                json response = json::parse(res->body);
                return {res->status, response["error"], true};
            } else {
                return {502, "Bad gateway", true};
            }
        } else {
            json response = json::parse(res->body);
            return {200, response["phase"], false};
        }
    } else {
        return {-1, "Connection failed", true};
    }
}

QString User::getAUEPhase() {
    Net::Result res = netHandler->retryRequest(3, [this]() {
        return getAUEPhaseImp();
    });

    return QString::fromStdString(res.message);
}
