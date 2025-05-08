#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QDate>
#include <vector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>

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

    void loadUserData(); // для отображения данных, работает как инит

signals:
    void S_ChangeForm(int formId);
    void S_DataLoaded();

private slots:
    void updateDeadlinesDisplay();
private:
    // Base
    Ui::Profile *ui;
    Net* netHandler;

    std::vector<Deadline> currentDeadlines;
    std::vector<Deadline> completedDeadlines;

    void setupUI();
    void loadCurrentDeadlines();
    void loadCompletedDeadlines();

    QWidget *currentDeadlinesContainer;
    QWidget *completedDeadlinesContainer;
    QVBoxLayout *currentLayout;
    QVBoxLayout *completedLayout;
};

#endif // PROFILE_H
