cmake_minimum_required(VERSION 3.19)
project(grape LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_resources(RESOURCE_FILES res.qrc)

qt_add_executable(grape
    WIN32 MACOSX_BUNDLE

    ${RESOURCE_FILES}

    # main.cpp and mainwindow
    main.cpp
    src/mainwindow/mainwindow.h
    src/mainwindow/mainwindow.cpp
    src/mainwindow/views-mainwindow.cpp
    src/mainwindow/net-mainwindow.cpp
    src/mainwindow/resize-mainwindow.cpp

    # Login page files
    src/login/login.h
    src/login/login.cpp

    # Dashboard page files
    src/dashboard/dashboard.h
    src/dashboard/dashboard.cpp
    src/dashboard/timer-dashboard.cpp
    src/dashboard/ayewords-dashboard.cpp
    src/dashboard/deadlines-dashboard.cpp
    src/dashboard/tasks-dashboard.cpp
    src/dashboard/notes-dashboard.cpp
    src/dashboard/settings-dashboard.cpp

    src/registration/registration.h
    src/registration/registration.cpp

    # Settings menu files
    src/settingsmenu/settingsmenu.h
    src/settingsmenu/settingsmenu.cpp

    # AddDeadlineDialog menu files
    src/adddeadlinedialog/adddeadlinedialog.h
    src/adddeadlinedialog/adddeadlinedialog.cpp

    #try add task
    src/addtasks/addtask.h
    src/addtasks/addtask.cpp


    # Misc files
    misc/clickQLabel.h
    misc/clickQLabel.cpp

    # Types files <- файлы с типами для простой передачи данных от модуля net к любой точке кода
    src/types/structs.h

    # =======
    # Снизу находятся файлы для работы с сетью
    # =======

    # Base NET Files <- интерфейс для взаимодействия со всеми нет хендлерами
    net/base-net/net.h
    net/base-net/net.cpp

    # User NET Files <- файлы класса для работы с пользователем(логин, регистрация, сохранение данных и т.д.)
    net/user-net/user-net.cpp

    # Dashboard NET Files <- файлы классов используемые на основной странице
    net/dashboard-net/deadline-net.cpp
    net/dashboard-net/task-net.cpp

    # Includes <- все зависимости
    net/include/httplib/httplib.h # <- библиотека запросов
    net/include/json/json.hpp # <- библиотека для парса json объектов
    net/include/hasher/hasher.h # <- мои старейшие файлы, хэширование пароля
    net/include/hasher/hasher.cpp
    src/addtasks/addtask.ui
    src/addtasks/addtask.h
    src/addtasks/addtask.cpp
    src/profile.ui
    src/profile/profile.ui
    src/profile/profile.ui
    src/profile/profile.ui # <- мои старейшие файлы, хэширование пароля
)

qt_add_ui(grape SOURCES
    src/login/login.ui
    src/dashboard/dashboard.ui
    src/registration/registration.ui
    src/settingsmenu/settingsmenu.ui
    src/adddeadlinedialog/adddeadlinedialog.ui

    #try
    src/addtasks/addtask.ui

)

target_link_libraries(grape
    PRIVATE
        Qt::Core
        Qt::Widgets
)

if(WIN32)
    set(LIBRARY_PATH "${CMAKE_SOURCE_DIR}/net/lib")
    target_link_libraries(grape PRIVATE
        ${LIBRARY_PATH}/libssl.a
        ${LIBRARY_PATH}/libcrypto.a
        ${LIBRARY_PATH}/libcrypt32.a
        ${LIBRARY_PATH}/libbcrypt.a
        ${LIBRARY_PATH}/libws2_32.a
    )
    set(INCLUDE_PATH "${CMAKE_SOURCE_DIR}/net/include")
    include_directories(${INCLUDE_PATH})
elseif(UNIX)
    find_package(OpenSSL REQUIRED)
    target_link_libraries(grape PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
    )
endif()

include(GNUInstallDirs)

install(TARGETS grape
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET grape
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
