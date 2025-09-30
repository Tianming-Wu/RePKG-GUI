cmake_minimum_required(VERSION 3.16)

project(RePKG-GUI
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    resources.qrc appicon.rc
    mainwindow.h mainwindow.cpp mainwindow.ui
    pgsettings.h pgsettings.cpp
    dropablelineedit.h dropablelineedit.cpp
    pkgcmdgenerator.h pkgcmdgenerator.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)
    find_package(Qt6 REQUIRED COMPONENTS LinguistTools)
    find_package(Qt6 REQUIRED COMPONENTS Core)

    qt_add_executable(RePKG-GUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

set(TS_FILES RePKG_GUI_zh_CN.ts)

qt_add_translations(RePKG-GUI
    TS_FILES ${TS_FILES}
    LUPDATE_OPTIONS -locations relative -no-obsolete
)


# Define target properties for Android with Qt 6 as:
#    set_property(TARGET RePKG-GUI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(RePKG-GUI SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(RePKG-GUI
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(RePKG-GUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(RePKG-GUI PRIVATE Qt6::Widgets)
target_link_libraries(RePKG-GUI PRIVATE Qt6::Core)
target_link_libraries(RePKG-GUI PRIVATE Qt6::Core)

target_include_directories(RePKG-GUI PRIVATE ${CMAKE_SOURCE_DIR})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.RePKG-GUI)
endif()
set_target_properties(RePKG-GUI PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS RePKG-GUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RePKG-GUI)
endif()
