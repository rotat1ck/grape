#include "../settingsmenu/settingsmenu.h"
#include "dashboard.h"
#include "ui_dashboard.h"
#include <QScrollBar>
#include <QVBoxLayout>
#include "ui_settingsmenu.h"
#include <QMessageBox>
#include <QPainterPath>
#include <QRegion>
#include <QPainter>


SettingsMenu::SettingsMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsMenu)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground, true);

    // Полное отключение всех эффектов
    setGraphicsEffect(nullptr);

    // Чистые стили с явным указанием всех параметров
    setStyleSheet(R"(
        #SettingsMenu {
            background-color: #D9D9D9;
            border-radius: 25px;
            border: 0px solid transparent; /* Явное отключение границы */
        }
        QPushButton {
            background-color: #F2F2F2;
            border-radius: 15px;
            padding: 8px;
            margin: 4px 8px;
            font-family: 'Comfortaa';
            font-size: 16px;
            color: black;
            border: none;
        }
        QPushButton:hover {
            background-color: #E5E5E5;
        }
    )");

    this->setObjectName("SettingsMenu"); // Для точного применения стилей
}

void SettingsMenu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Только фон, без каких-либо границ
    painter.setBrush(QColor("#D9D9D9"));
    painter.setPen(Qt::NoPen); // Критически важно - никакой границы
    painter.drawRoundedRect(rect(), 25, 25);
}





SettingsMenu::~SettingsMenu()
{
    delete ui;
}





void Dashboard::on_menuSettings_clicked()
{
    if (!settingsMenu) {
        settingsMenu = new SettingsMenu(this);
    }

    // Получаем позицию кнопки относительно окна Dashboard
    QPoint buttonPos = ui->menuSettings->mapToGlobal(QPoint(-74, 84));
    settingsMenu->move(buttonPos.x() + ui->menuSettings->width() + 5, buttonPos.y());
    settingsMenu->show();
}

void SettingsMenu::on_designButton_clicked()
{
    close();
}

void SettingsMenu::on_profileButton_clicked()
{
    close();
}

void SettingsMenu::on_exitButton_clicked()
{
    close();
}
