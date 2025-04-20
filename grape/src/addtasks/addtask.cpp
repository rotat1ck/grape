#include "addtask.h"
#include "ui_addtask.h"
#include <QMessageBox>
#include <QPushButton>

addtask::addtask(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addtask)
{
    ui->setupUi(this);
    ui->NameTaskLine->setStyleSheet("font-size: 20px; font-family: 'Comfortaa';");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    resetDialog();
    connect(ui->AddButton, &QPushButton::clicked, this, &addtask::accept);
    connect(ui->CancelButton, &QPushButton::clicked, this, &addtask::reject);
}

addtask::~addtask()
{
    delete ui;
}

QString addtask::taskName() const
{
    return ui->NameTaskLine->text();
}

void addtask::resetDialog()
{
    ui->NameTaskLine->clear();
}

void addtask::accept()
{
    // проверка на пустое имя задачи
    QString name = taskName().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поле не может быть пустым.");
        return;
    }
    if (name.length() > 30) {
        QMessageBox::warning(this, "Ошибка", "Название задачи слишком длинное.");
        return;
    }
    QDialog::accept();
}

void addtask::reject()
{
    QDialog::reject();
}
