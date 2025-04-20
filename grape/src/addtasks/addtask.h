#ifndef ADDTASK_H
#define ADDTASK_H

#include <QDialog>
#include <QString>

namespace Ui {
class addtask;
}

class addtask : public QDialog
{
    Q_OBJECT
public:
    explicit addtask(QWidget *parent = nullptr);
    ~addtask();

    QString taskName() const;  // Геттер для названия задачи

protected:
    void accept() override;  // Обработка подтверждения
    void reject() override;  // Обработка отмены

private:
    Ui::addtask *ui;
    void resetDialog();  // Сброс состояния диалога

    // QWidget interface
protected:
    // void showEvent(QShowEvent *event) override;  // Для начальной настройки
};

#endif // ADDTASK_H
