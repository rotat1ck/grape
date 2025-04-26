
#include "dashboard.h"
#include "ui_dashboard.h"
#include <QVBoxLayout>
#include <QLabel>

// Инициализация UI
void Dashboard::notesUI()
{
    QTextEdit *textEdit = new QTextEdit(this);
    textEdit->setGeometry(25, 376, 200, 312); // Позиция, размер 200x100

    // перенос и отступ
    textEdit->setWordWrapMode(QTextOption::WordWrap); // перенос по словам
    textEdit->setStyleSheet(R"(
    QTextEdit {
        background: #D9D9D9;
        border-radius: 20px;
        color: #786060;
        border: 2px solid #CCCCCC;
        padding: 5px;
        margin: 0px;
        font-size: 20px;
        font-family: Comfortaa;
    }
)");

    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
