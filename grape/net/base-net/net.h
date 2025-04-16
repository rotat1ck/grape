#ifndef NET_H
#define NET_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../include/httplib/httplib.h"
#include "../include/json/json.hpp"
#include "../include/hasher/hasher.h"
#include <QString>
#include <QObject>

using json = nlohmann::json;

class User;

// Base class
class Net : public QObject {
    Q_OBJECT
protected:
    toHash hasher;

    struct Result {
        int status;
        std::string message;
        bool isFailure;
    };
signals:
    void S_CacheToken(std::string token);

public:
    httplib::Client* cl = new httplib::Client("https://grape.rotatick.ru");

    std::string token;
    User* user;

    Net();
    ~Net();

    std::string getHashed(std::string msg);
    bool checkServerStatus();
    void cacheToken(std::string token);
};

class User {
public:
    User(Net* netHandler) : netHandler(netHandler) { }

    bool sendLoginRequest(QString usernameEntry, QString passwordEntry);
    bool sendRegisterRequest(QString emailEntry, QString usernameEntry, QString passwordEntry);

    bool getUserData();

    // Сделать структуру в src/types/structs.h
    //std::vector<std::string> getUserDeadlines();

    // Сделать структуру в src/types/structs.h
    //std::vector<std::string> getUserTasks();

    // Сделать структуру в src/types/structs.h
    //std::vector<std::string> getUserSettings();
private:
    Net* netHandler;
};

#endif // NET_H
