cmake_minimum_required(VERSION 3.16)

project(SystemMonitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Qml Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appSystemMonitor
    main.cpp
)

qt_add_qml_module(appSystemMonitor
    URI SystemMonitor
    QML_FILES
        Main.qml
        SOURCES systeminfo.h systeminfo.cpp
        QML_FILES SidebarButton.qml
        RESOURCES Resources.qrc
        QML_FILES
        QML_FILES ProcessorPage.qml
        QML_FILES MemoryPage.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSystemMonitor PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSystemMonitor
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSystemMonitor
    PRIVATE
    Qt::Charts
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

include(GNUInstallDirs)
install(TARGETS appSystemMonitor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
