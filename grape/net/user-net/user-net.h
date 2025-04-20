// #ifndef USER-NET_H
// #define USER-NET_H

// #define CPPHTTPLIB_OPENSSL_SUPPORT
// #include "../include/httplib/httplib.h"
// #include "../include/hasher/hasher.h"
// #include <QString>
// #include <QObject>
// #include <vector>

// class Net;

// class User : public QObject {
//     Q_OBJECT

// private:
//     Net* netHandler;
// signals:
//     void S_CacheToken(std::string token);

// public:
//     User(Net* parent = nullptr) : netHandler(parent) { }

//     void sendLoginRequest(QString usernameEntry, QString passwordEntry);

//     void getUserData();

//     // Сделать структуру в src/types/structs.h
//     //std::vector<std::string> getUserDeadlines();

//     // Сделать структуру в src/types/structs.h
//     //std::vector<std::string> getUserTasks();

//     // Сделать структуру в src/types/structs.h
//     //std::vector<std::string> getUserSettings();
// };

// #endif // USER-NET_H
