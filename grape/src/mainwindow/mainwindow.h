#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>

#include "../login/login.h"
#include "../dashboard/dashboard.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // - - UI - -

    // Главный объект интерфейса, через него идет переключение форм дизайна,
    // т.е - этот объект определяет что будет находиться на экране
    QWidget* centralWidget;
    QStackedLayout* layout;

    // Пример того как создаются объекты имееющие графический интерфейс
    // Создание указателя на объект требуется для последующей передачи в layout
    Login* login; // <- описание объекта в src/login/login.h
    Dashboard* dashboard;
};

#endif // MAINWINDOW_H
