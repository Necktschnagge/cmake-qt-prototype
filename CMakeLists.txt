cmake_minimum_required(VERSION 3.5)

project(Tobor_try_46757298346582354 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (DEFINED USE_QT5)
	set(USE_QT6 FALSE)
	message("USE QT 5")
else()
	set(USE_QT6 TRUE)
	message("USE QT 6")

endif()


if(USE_QT6)
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Svg SvgWidgets)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg SvgWidgets)

else()
    find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Svg)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg)

endif()


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Tobor_try_46757298346582354
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Tobor_try_46757298346582354 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Tobor_try_46757298346582354 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Tobor_try_46757298346582354
            ${PROJECT_SOURCES}
        )
    endif()
endif()

if(USE_QT6)
    target_link_libraries(Tobor_try_46757298346582354 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Svg Qt${QT_VERSION_MAJOR}::SvgWidgets)
else()
    target_link_libraries(Tobor_try_46757298346582354 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Svg)
endif()

set_target_properties(Tobor_try_46757298346582354 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Tobor_try_46757298346582354
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Tobor_try_46757298346582354)
endif()
