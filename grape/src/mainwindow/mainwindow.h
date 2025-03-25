#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>

#include "../test/test.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // - - UI - -

    // Главный объект интерфейса, через него идет переключение форм дизайна,
    // т.е - этот объект определяет что будет находиться на экране
    QStackedLayout* layout;

    // Пример того как создаются объекты имееющие графический интерфейс
    // Создание указателя на объект требуется для последующей передачи в layout
    Test* test; // <- описание объекта в src/test/test.h
};

#endif // MAINWINDOW_H
