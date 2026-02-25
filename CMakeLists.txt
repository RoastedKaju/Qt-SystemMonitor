cmake_minimum_required(VERSION 3.16)

project(SystemMonitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Charts Core Widgets Gui Qml)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appSystemMonitor
    main.cpp
)

qt_add_qml_module(appSystemMonitor
    URI SystemMonitor
    VERSION 1.0
    QML_FILES
        Main.qml
        RESOURCES Resources.qrc
        QML_FILES Utils/SidebarButton.qml
        QML_FILES Utils/ProcessorPage.qml
        QML_FILES Utils/MemoryPage.qml
        QML_FILES Utils/GPUPage.qml
        QML_FILES Utils/EthernetPage.qml
        SOURCES Backend/processor_backend.h Backend/processor_backend.cpp
        SOURCES Backend/memory_backend.h Backend/memory_backend.cpp
        SOURCES Backend/gpu_backend.h Backend/gpu_backend.cpp
        SOURCES Backend/ethernet_backend.h Backend/ethernet_backend.cpp
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

# Add hwinfo submodule
add_subdirectory(vendor/hwinfo)

target_link_libraries(appSystemMonitor
    PRIVATE
    Qt6::Quick
    Qt::Charts
    Qt6::Core
    Qt6::Widgets
    Qt::Gui
    Qt::Qml
    lfreist-hwinfo::hwinfo
)

if(WIN32)
    target_link_libraries(appSystemMonitor
        PRIVATE
        iphlpapi
        ws2_32
    )
endif()

target_include_directories(appSystemMonitor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Backend)

include(GNUInstallDirs)
install(TARGETS appSystemMonitor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
