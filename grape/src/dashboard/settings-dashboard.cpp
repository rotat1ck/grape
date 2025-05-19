#include "../settingsmenu/settingsmenu.h"
#include "dashboard.h"
#include "ui_dashboard.h"

#include "ui_settingsmenu.h"



SettingsMenu::SettingsMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsMenu)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground, true);
}

void SettingsMenu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Только фон, без каких-либо границ
    painter.setBrush(QColor("#706B68"));
    painter.setPen(Qt::NoPen); // Критически важно - никакой границы
    painter.drawRoundedRect(rect(), 25, 25);
}

SettingsMenu::~SettingsMenu()
{
    delete ui;
}

void Dashboard::on_menuSettings_clicked()
{
    // Получаем позицию кнопки относительно окна Dashboard
    QPoint buttonPos = ui->menuSettings->mapToGlobal(QPoint(-74, 84));
    settingsMenu->move(buttonPos.x() + ui->menuSettings->width() + 5, buttonPos.y());
    settingsMenu->show();
}

void SettingsMenu::on_designButton_clicked()
{
    close();
}

void SettingsMenu::on_exitButton_clicked()
{
    emit S_ChangeForm(0);
    close();
}
