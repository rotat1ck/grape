#ifndef USER-NET_H
#define USER-NET_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../include/httplib/httplib.h"
#include "../include/hasher/hasher.h"
#include <QString>
#include <QObject>

class User : public QObject {
    Q_OBJECT

private:
    QObject* netHandler;
signals:
    void S_CacheToken(std::string token);

public:
    User(QObject* parent = nullptr) : netHandler(parent) { }

    void sendLoginRequest(QString username, QString password);
};

#endif // USER-NET_H
