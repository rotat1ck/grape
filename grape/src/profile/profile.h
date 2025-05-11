#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QDate>
#include <vector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>

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
    void initProfile();
    ~Profile();

signals:
    void S_ChangeForm(int formId);

private slots:
    void on_LeftSwipeButton_clicked();

private:
    Ui::Profile *ui;
    Net* netHandler;

    std::vector<Deadline> allDeadlines;
    std::vector<Deadline> currentDeadlines;
    std::vector<Deadline> completedDeadlines;

    QVBoxLayout* currentLayout;
    QVBoxLayout* completedLayout;

    void setupUI();
    void loadUserData();
    void loadCurrentDeadlines();
    void loadCompletedDeadlines();
    void updateDeadlinesDisplay();
};

#endif // PROFILE_H
