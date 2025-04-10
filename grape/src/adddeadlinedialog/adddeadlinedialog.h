#ifndef ADDDEADLINEDIALOG_H
#define ADDDEADLINEDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class AddDeadlineDialog;
}

class AddDeadlineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDeadlineDialog(QWidget *parent = nullptr);
    ~AddDeadlineDialog();

    QString getDeadlineName() const;
    QDate getDeadlineDate() const;

protected:
    void accept() override;
    void reject() override;

private slots:
    void on_calendarButton_clicked();

private:
    Ui::AddDeadlineDialog *ui;
    void resetDialog();
};

#endif // ADDDEADLINEDIALOG_H
