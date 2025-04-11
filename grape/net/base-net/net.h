#ifndef NET_H
#define NET_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../include/httplib/httplib.h"
#include "../include/hasher/hasher.h"

#include "../user-net/user-net.h"

#include <QString>
#include <QObject>

class Net : public QObject {
    Q_OBJECT
private:
    httplib::Client cl;
    toHash hasher;

    struct Result {
        int status;
        std::string message;
        bool isFailure;
    };
signals:
    void S_CacheToken(std::string token);

public:
    std::string token;
    User* user;

    Net();
    ~Net();

    std::string getHashed(std::string msg);
    bool checkServerStatus();
    void cacheToken(std::string token);
};

#endif // NET_H
