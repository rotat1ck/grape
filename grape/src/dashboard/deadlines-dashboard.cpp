#include "dashboard.h"
#include "ui_dashboard.h"
#include <QScrollBar>
#include <QVBoxLayout>
#include <algorithm>

#include "../adddeadlinedialog/adddeadlinedialog.h"

void Dashboard::setupDeadlinesBox()
{
    deadlineLayout = new QVBoxLayout(ui->DeadlinesBoxContents);
    deadlineLayout->setAlignment(Qt::AlignTop);
    deadlineLayout->setSpacing(5);


    deadlines = netHandler->deadlines->getUserDeadlines();
    updateDeadlinesList();
}

void Dashboard::on_addDeadlineButton_clicked()
{
    static bool isProcessing = false;
    if (isProcessing) {
        return;
    }

    isProcessing = true;

    AddDeadlineDialog* dialog = new AddDeadlineDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    connect(dialog, &QDialog::finished, this, [=](int result) {
        if (result == QDialog::Accepted) {
            netHandler->deadlines->addUserDeadline(dialog->getDeadlineName(), dialog->getDeadlineDate());
            deadlines = netHandler->deadlines->getUserDeadlines();
            std::sort(deadlines.begin(), deadlines.end());
            updateDeadlinesList();
        }
        isProcessing = false;
    });

    dialog->show();
}

void Dashboard::updateDeadlinesList() {
    if (deadlineLayout) {
        QLayoutItem* item;
        while ((item = deadlineLayout->takeAt(0))) {
            delete item->widget();
            delete item;
        }
    }

    for (Deadline deadline : deadlines) {
        addNewDeadline(deadline);
    }
}


void Dashboard::addNewDeadline(Deadline& deadline) {
    QDate today = QDate::currentDate();
    int daysLeft = today.daysTo(deadline.date);

    QString backgroundColor = "#D9D9D9";  // Базовый цвет (более 3 дней)
    QString textColor = "#6D5959";        // Тёмно-серый для текста
    QString borderColor = "#D4C1C1";      // Светло-розовый для рамки
    QString accentColor = "#8B7E7E";      // Акцентный цвет для даты

    if (daysLeft < 0) {
        backgroundColor = "#FFE6E6";  // Просрочено
        borderColor = "#FFCCCC";
        accentColor = "#CC7777";
    }
    else if (daysLeft == 0) {
        backgroundColor = "#EC9797";  // today 0 day
        borderColor = "#FFD6D6";
        accentColor = "#CC8888";
    }
    else if (daysLeft == 1) {
        backgroundColor = "#FFE6E6";  // 1 день
        borderColor = "#FFD6D6";
        accentColor = "#CC8888";
    } else if (daysLeft == 2) {
        backgroundColor = "#FFECD9";  // 2 дня
        borderColor = "#FFE0C2";
        accentColor = "#CCA088";
    } else if (daysLeft == 3) {
        backgroundColor = "#FFF2E6";  // 3 дня
        borderColor = "#FFE6D1";
        accentColor = "#CCB088";
    }

    QString daysLeftText;

    if (daysLeft < 0) {
        daysLeftText = "Просрочено";
    } else if (daysLeft == 0) {
        daysLeftText = "Сегодня";
    } else {
        if (daysLeft == 1) {
            daysLeftText = QString("%1 %2").arg(daysLeft).arg("день");
        } else if (daysLeft < 5) {
            daysLeftText = QString("%1 %2").arg(daysLeft).arg("дня");
        } else {
            daysLeftText = QString("%1 %2").arg(daysLeft).arg("дней");
        }
    }


    QString deadlineItemStyleSheet =
        "background-color: " + backgroundColor + ";"
        "color: #000;"
        "border-radius: 10px;"
        "padding: 8px;"
    ;

    QWidget* deadlineItem = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(deadlineItem); // Create a layout for the deadlineItem
    deadlineItem->setStyleSheet(deadlineItemStyleSheet);

    QLabel* deadlineItemText = new QLabel(deadline.name, deadlineItem);
    deadlineItemText->setStyleSheet(R"(
        font-family: 'Comfortaa';
        font-size: 18px;
        color: #333;
        margin-left: 5px;
    )");
    deadlineItemText->setAlignment(Qt::AlignLeft);


    QLabel* deadlineItemDate = new QLabel(daysLeftText, deadlineItem);
    deadlineItemDate->setStyleSheet(R"(
        font-family: 'Comfortaa';
        font-size: 16px;
        color: #333;
        margin-left: 5px;
    )");

    deadlineItemText->setWordWrap(true); // перенос слов
    deadlineItemDate->setAlignment(Qt::AlignRight);
    //deadlineItemText->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    deadlineItemText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);



    QPushButton* deleteBtn = new QPushButton("×");
    deleteBtn->setStyleSheet(R"(
        color: #FF6B6B;
        font-size: 30px;
        border: none;
        background: transparent;
    )");
    deleteBtn->setCursor(Qt::PointingHandCursor);

    connect(deleteBtn, &QPushButton::clicked, [=]() {
        auto it = std::find_if(deadlines.begin(), deadlines.end(), [&deadline](const Deadline& d) {
            return &d == &deadline; // Compare addresses
        });
        if (it != deadlines.end()) {
            deadlines.erase(it);
        }
        deadlineLayout->removeWidget(deadlineItem);
        netHandler->deadlines->deleteUserDeadline(deadline.id);
        delete deadlineItem;
    });

    layout->addWidget(deadlineItemText, 1); // Add the name label to the layout
    layout->addWidget(deadlineItemDate, 2);  // Add the date label to the layout
    layout->addWidget(deleteBtn);
    deadlineItem->setLayout(layout); // Set the layout to the deadlineItem

    deadlineLayout->addWidget(deadlineItem);
}
