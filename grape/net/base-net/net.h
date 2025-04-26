#ifndef NET_H
#define NET_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
// Внешние зависимости
#include "../include/httplib/httplib.h"
#include "../include/json/json.hpp"
#include "../include/hasher/hasher.h"

// Используемые типы
#include <QString>
#include <QObject>
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <functional>
#include <vector>

// Структуры
#include "../../src/types/structs.h"

using json = nlohmann::json;

class User;
class Tasks;
class Deadlines;


// =======
// Base class
// =======

class Net : public QObject {
    Q_OBJECT

signals:
    void S_CacheToken(std::string token);

public:
    // Клиент
    httplib::Client* cl = new httplib::Client("https://grape.rotatick.ru");

    // Пользователькие данные
    std::string email;
    std::string username;
    std::string password;

    /*
        Структура возвращаемого ответа
        В функциях возвращающий данный тип return будет выглядеть примерно так:
        return {< КОД ОТВЕТА>, < ТЕЛО ОТВЕТА >, < ЯВЛЯЕТСЯ ЛИ ЗАПРОС НЕУДАЧНЫМ >};
        return {200, "Успех, гойда, гойда", false}; <- т.е false что НЕ является неудачей
    */
    struct Result {
        int status;
        std::string message;
        bool isFailure;
    };

    // Токен и доп. объекты расширения сетевого обработчика(Net класса)
    std::string token;
    User* user;
    Tasks* tasks;
    Deadlines* deadlines;

    Net();
    ~Net();

    // Базовые функции
    std::string getHashed(std::string msg);
    bool checkServerStatus();
    Result retryRequest(int retryCount, std::function<Net::Result()> func);
    bool updateToken();

private:
    toHash hasher;
    void cacheToken(std::string token);
};


// =======
// User class
// =======

class User {
private:
    Net* netHandler;

    /*
        Внутренние функции, используются из-под публичных
        Здесь находяться функции с самой логикой запросов,
        Публичные функции всего лишь обертка для них
        Я сделал это для обязательных повторов запросов в указанном количестве

        Пример:
        из кода приложения вызывается netHandler->user->sendLoginRequest(< ЛОГИН >, < ПАРОЛЬ >)
        при наличии такой структуры и функции на повтор запросов в основном классе Net - retryRequest
        мы будем уверенны что запрос дошел и был обработан, вне зависимости успешен он или нет

        Приписка Imp(Implementation) в конце означает что функция является обрабатывающей для своей обертки
    */
    Net::Result sendLoginRequestImp();
    Net::Result sendRegisterRequestImp();

public:
    User(Net* netHandler) : netHandler(netHandler) { }

    // Функция которая обновляет параметр token основного класса Net
    bool updateToken();

    /*
        Функции обертки для функций обработчиков
        Именно их необходимо вызывать из любой точки кода приложения
        Внутри проходит получения параметров и вызов функции обработчика
        с указанным кол-вом попыток получения ответа от сервера
    */
    Net::Result sendLoginRequest(QString usernameEntry, QString passwordEntry);
    Net::Result sendRegisterRequest(QString emailEntry, QString usernameEntry, QString passwordEntry);

    // Сделать структуру в src/types/structs.h
    //std::vector<std::string> getUserDeadlines();

    // Сделать структуру в src/types/structs.h
    //std::vector<std::string> getUserSettings();
};


// =======
// Tasks class
// =======

class Tasks {
private:
    Net* netHandler;

    Net::Result getUserTasksImp();

    Net::Result addUserTaskImp(QString content);
    Net::Result deleteUserTaskImp(int id);
public:
    Tasks(Net* netHandler) : netHandler(netHandler) { }

    std::vector<Task> getUserTasks();

    Net::Result addUserTask(QString content);

    Net::Result deleteUserTask(int id);
};

// =======
// Deadlines class
// =======

class Deadlines {
private:
    Net* netHandler;

    Net::Result getUserDeadlinesImp();

    Net::Result addUserDeadlineImp(QString content, QDate endstampEntry);

    Net::Result deleteUserDeadlineImp(int id);
public:
    Deadlines(Net* netHandler) : netHandler(netHandler) { }

    std::vector<Deadline> getUserDeadlines();

    Net::Result addUserDeadline(QString content, QDate endstampEntry);

    Net::Result deleteUserDeadline(int id);
    Net::Result deleteUserTask(int id);
};

#endif // NET_H
