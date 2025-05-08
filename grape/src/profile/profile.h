#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QTextBrowser>
#include <QDate>
#include <vector>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "../../net/base-net/net.h"
#include "../types/structs.h"

namespace Ui {
class Profile;
}

class Profile : public QWidget
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr, Net* netHandler = nullptr);
    ~Profile();

signals:
    void S_ChangeForm(int formId);

private slots:

private:
    // Base
    Ui::Profile *ui;
    Net* netHandler;
};

#endif // PROFILE_H
