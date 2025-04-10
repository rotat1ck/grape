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

    # Misc files
    misc/clickQLabel.h
    misc/clickQLabel.cpp
    src/mainwindow/resize-mainwindow.cpp


)

qt_add_ui(grape SOURCES
    src/login/login.ui
    src/dashboard/dashboard.ui
    src/registration/registration.ui
)

target_link_libraries(grape
    PRIVATE
        Qt::Core
        Qt::Widgets
)

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
