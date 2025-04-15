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

}
