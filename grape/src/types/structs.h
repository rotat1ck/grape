#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>
#include <QDate>

struct Deadline {
    int id;
    QString name;
    QDate date;
    bool operator<(const Deadline& other) {
        return date < other.date;
    }
};

struct Task {
    int id;
    QString name;
};

struct Settings {

};

#endif // STRUCTS_H
