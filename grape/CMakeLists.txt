cmake_minimum_required(VERSION 3.19)
project(grape LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(grape
    WIN32 MACOSX_BUNDLE

    # main.cpp and mainwindow
    main.cpp
    src/mainwindow/mainwindow.cpp
    src/mainwindow/mainwindow.h


    # Файлы тестирования автоподгона объектов
    # при изменении размеров окна
    src/test/test.cpp
    src/test/test.h
)

qt_add_ui(grape SOURCES
    src/test/test.ui
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
