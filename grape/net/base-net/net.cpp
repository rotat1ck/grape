#include "net.h"

Net::Net() {
    user = new User(this);
    cl->set_connection_timeout(0, 500000);
    cl->set_default_headers({{"Host", "grape.rotatick.ru"}});

    connect(this, &Net::S_CacheToken, this, &Net::cacheToken);
}

Net::~Net() {
    delete cl;
    delete user;
}

std::string Net::getHashed(std::string msg) {
    return hasher.hash(msg);
}

void Net::cacheToken(std::string token) {
    this->token = token;
}

bool Net::checkServerStatus() {
    std::string endpoint = "/api/health";

    if (auto res = cl->Get(endpoint)) {
        if (res->status != 200) {
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}

Net::Result Net::retryRequest(int retryCount, std::function<Net::Result()> func) {
    int currentTry = 1;
    while (currentTry <= retryCount) {
        Result returned = func();
        if (!returned.isFailure) {
            return {returned.status, returned.message, returned.isFailure};
        } else if (returned.status == 401) {
            return {returned.status, "Incorrect username/email or password", true};
        } else if (returned.status == 403) {
            updateToken();
        }
        currentTry++;
    }
    return {0, "Connection failed", true};
}

bool Net::updateToken() {
    std::string tempUsername = "username=" + username;
    std::string tempPassword = "password=" + getHashed(password);

    std::string endpoint = "/api/users/login?" + tempUsername + "&" + tempPassword;
    if (auto res = cl->Post(endpoint)) {
        if (res->status != 200) {
            return false;
        } else {
            json response = json::parse(res->body);
            emit S_CacheToken(response["token"]);
            return true;
        }
    } else {
        return false;
    }
}
