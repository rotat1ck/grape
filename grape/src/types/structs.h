#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>
#include <QDate>

struct Deadline {
    QString name;
    QDate date;
    bool operator<(const Deadline& other) {
        return date < other.date;
    }
};

struct Task {

};

struct Settings {

};

#endif // STRUCTS_H
