#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>
#include <QMouseEvent>

#include "../../net/base-net/net.h"

#include "../login/login.h"
#include "../dashboard/dashboard.h"
#include "../registration/registration.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // - - NET - -
    // Реализация функций в src/mainwindow/net-mainwindow.cpp
    void setupNetHandlers();

    // - - UI - -
    // Реализация функций в src/mainwindow/views-mainwindow.cpp
    void setupViews();
    void setupConnects();
    void changeForm(int formId);

    void defineStartWindow();

private:
    // - - POSITION - -
    QPoint dragStartPosition; // позиция курсора при переносе окна
    bool dragging = false; // статус переноса окна
    bool resizing = false; // статус расширения окна

    // - - NET - -
    Net* netHandler;

    // - - UI - -
    // Главный объект интерфейса, через него идет переключение форм дизайна,
    // т.е - этот объект определяет что будет находиться на экране
    QWidget* centralWidget;
    QStackedLayout* layout;

    // Пример того как создаются объекты имееющие графический интерфейс
    // Создание указателя на объект требуется для последующей передачи в layout
    Login* login; // <- описание объекта в src/login/login.h
    Registration* registration; // <- описание объекта в src/registration/registration.h
    Dashboard* dashboard; // <- описание объекта в src/dashboard/dashboard.h

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H
