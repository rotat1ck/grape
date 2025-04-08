#include "mainwindow.h"

// функция исполняет задачу по переключению окон интерфейса по входным данным
void MainWindow::changeForm(int formId) {
    switch(formId) {
        case 0: { // окно логина
            layout->setCurrentWidget(login);
            setFixedSize(640, 720);
            setWindowFlags(Qt::Window);
            show();
            break;
        } case 1: { // окно регистрации
            layout->setCurrentWidget(registration);
            setFixedSize(640, 720);
            setWindowFlags(Qt::Window);
            show();
            break;
        } case 2: { // окно основной рабочей зоны
            layout->setCurrentWidget(dashboard);
            setWindowFlags(Qt::FramelessWindowHint);
            setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
            setMinimumSize(0,0);
            show();
            break;
        }
    }
}

// функция настраивает основное окно и создает все окна интерфейса
void MainWindow::setupViews() {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    layout = new QStackedLayout(centralWidget); // <- описание объекта в src/mainwindow/mainwindow.h


    login = new Login(this);
    registration = new Registration(this);
    dashboard = new Dashboard(this);

    layout->addWidget(login); /* <- таким образом добавляется объект класса с интерфейсом
        в layout, это необходимо для того чтобы layout при вызове метода setCurrentWidget
        мог отрисовать объект на экране */
    layout->addWidget(registration);
    layout->addWidget(dashboard);
}

// функция будет настраивать коннекты, для общения между разными частями программы
// рекомендую заранее почитать про connect и disconnect
void MainWindow::setupConnects() {
    // - - LOGIN - -
    connect(login, &Login::S_ChangeForm, this, &MainWindow::changeForm);

    // - - Rehistration -  -
    connect(registration, &Registration::S_ChangeForm, this, &MainWindow::changeForm);
}

// функция будет определять стартовое окно после запуска приложения
// т.е. если логин и пароль записан то показать спиннер загрузки
// и осуществить запрос со страницы логина
void MainWindow::defineStartWindow() {
    // показываю окно логина, т.к. логики обработки наличия логина и пароля еще нет
    changeForm(0);
}
