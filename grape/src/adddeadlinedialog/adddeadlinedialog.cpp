#include "adddeadlinedialog.h"
#include "ui_adddeadlinedialog.h"
#include <QDate>
#include <QCalendarWidget>
#include <QMouseEvent>

AddDeadlineDialog::AddDeadlineDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddDeadlineDialog)
{
    ui->setupUi(this);
    
    // Устанавливаем флаги окна
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    
    // Инициализация полей
    resetDialog();

    // Устанавливаем календарь всегда видимым при клике
    ui->dateEdit->setCalendarPopup(true);
}

AddDeadlineDialog::~AddDeadlineDialog()
{
    delete ui;
}

QString AddDeadlineDialog::getDeadlineName() const
{
    return ui->nameEdit->text();
}

QDate AddDeadlineDialog::getDeadlineDate() const
{
    return ui->dateEdit->date();
}

void AddDeadlineDialog::resetDialog()
{
    ui->nameEdit->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate::currentDate());
}

void AddDeadlineDialog::accept()
{
    QString name = getDeadlineName().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поле не может быть пустым.");
        return;
    }
    if (name.length() > 30) {
        QMessageBox::warning(this, "Ошибка", "Название дедлайна слишком длинное.");
        return;
    }
    QDialog::accept();
}

void AddDeadlineDialog::reject()
{
    QDialog::reject();
}

void AddDeadlineDialog::on_calendarButton_clicked()
{
    // Эмулируем клик по кнопке календаря в QDateEdit
    QPoint buttonPos = ui->dateEdit->rect().topRight();
    QMouseEvent pressEvent(QEvent::MouseButtonPress, buttonPos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QMouseEvent releaseEvent(QEvent::MouseButtonRelease, buttonPos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    
    QApplication::sendEvent(ui->dateEdit, &pressEvent);
    QApplication::sendEvent(ui->dateEdit, &releaseEvent);
}
