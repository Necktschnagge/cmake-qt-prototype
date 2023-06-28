cmake_minimum_required(VERSION 3.5)


############### Names ###############
set(PROJECT_NAME Tobor)


############### Preprocessor Macros ###############
add_compile_definitions(GIT_REPOSITORY_URL="https://github.com/Necktschnagge/cmake-qt-prototype")


############### Project Decklaration ###############
project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)


############### Check Platform ###############
message("CMake is checking for CMAKE_SYSTEM_PROCESSOR containing arm to detect if running on Raspberry Pi:")
message("CMAKE_SYSTEM_PROCESSOR is: " ${CMAKE_SYSTEM_PROCESSOR})
if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
	message("Running on Raspberry Pi.")
	set(on_target_platform true)
else(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
	message("Running on Development or Test Platform.")
	set(on_target_platform false)
endif()
if(UNIX AND NOT APPLE)
	set(LINUX true)
else()
	set(LINUX false)
endif()
if (WIN32)
	message("Running on WIN32.")

SET(QT_MISSING True)

IF(MSVC)
    GET_FILENAME_COMPONENT(QT_BIN [HKEY_CURRENT_USER\\Software\\Classes\\Applications\\QtProject.QtCreator.cpp\\shell\\Open\\Command] PATH)

    STRING(REPLACE "/Tools" ";" QT_BIN "${QT_BIN}")
    
    # Azure Hack
    set(QT_BIN D:/a/1/b/Qt)

    LIST(GET QT_BIN 0 QT_BIN)
    FILE(GLOB QT_VERSIONS "${QT_BIN}/5.*")
    LIST(SORT QT_VERSIONS)

    LIST(REVERSE QT_VERSIONS)

    LIST(GET QT_VERSIONS 0 QT_VERSION)

    STRING(REPLACE "//" "/"  QT_VERSION "${QT_VERSION}")

if     ((MSVC_VERSION GREATER_EQUAL "1920") AND (IS_DIRECTORY "${QT_VERSION}/msvc2019"))
    set(QT_MSVC "2019")
elseif ((MSVC_VERSION GREATER_EQUAL "1920") AND (IS_DIRECTORY "${QT_VERSION}/msvc2019_64"))
    set(QT_MSVC "2019")
elseif ((MSVC_VERSION GREATER_EQUAL "1910") AND (IS_DIRECTORY "${QT_VERSION}/msvc2017"))
    set(QT_MSVC "2017")
elseif ((MSVC_VERSION GREATER_EQUAL "1910") AND (IS_DIRECTORY "${QT_VERSION}/msvc2017_64"))
    set(QT_MSVC "2017")
elseif (MSVC_VERSION GREATER_EQUAL "1900")
    set(QT_MSVC "2015")
else()
    MATH(EXPR QT_MSVC "2000 + (${MSVC_VERSION} - 500) / 100")
endif()

# Azure Hack
MESSAGE("---hahn--- QT_MSVC: ${QT_MSVC}")
MESSAGE("---hahn--- QT_VERSION: ${QT_VERSION}")
set(QT_MSVC "2019")
set(QT_VERSION D:/a/1/b/Qt/5.15.2)

MESSAGE("---hahn--- MSVC_VERSION: ${MSVC_VERSION}")
MESSAGE("---hahn--- QT_MSVC: ${QT_MSVC}")
MESSAGE("---hahn--- QT_VERSION: ${QT_VERSION}")

    IF(CMAKE_SYSTEM_PROCESSOR MATCHES 64)
        SET(QT_MSVC "${QT_MSVC}_64")
    ENDIF()
    SET(QT_PATH "${QT_VERSION}/msvc${QT_MSVC}")
    SET(QT_MISSING False)
ENDIF()

IF(NOT QT_MISSING)
    MESSAGE("-- Qt found: ${QT_PATH}")
    SET(Qt5_DIR "${QT_PATH}/lib/cmake/Qt5/")
    SET(QT_DIR "${QT_PATH}/lib/cmake/Qt5/")
    MESSAGE("---hahn--- Qt5_DIR: ${Qt5_DIR}")
    MESSAGE("---hahn--- QT_DIR: ${Qt5_DIR}")
ENDIF()

endif()
if (LINUX)
	message("Running on LINUX.")
endif()
if (APPLE)
	message("Running on APPLE.")
	set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE)
endif()
if (UNIX)
	message("Running on UNIX.")
endif()


############### Language and Flags ###############
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_EXTENSIONS False)
set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /Ob2 /DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "/MT /Zi /Ob0 /Od /RTC1")


############### Libraries ###############
include_directories(SYSTEM extern/spdlog/include)
add_subdirectory(extern/googletest)

#set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/6.5.0/msvc2019_64)
#set(QT_DIR "C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5")
#set(Qt5_DIR "C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5")

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
MESSAGE("---hahn--- QT_VERSION_MAJOR: ${QT_VERSION_MAJOR}")
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
set(QT_VERSION_MAJOR 5)
MESSAGE("---hahn--- QT_VERSION_MAJOR: ${QT_VERSION_MAJOR}")
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS SvgWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
#find_package(Qt6 REQUIRED COMPONENTS SvgWidgets)
#find_package(Qt6 REQUIRED COMPONENTS Svg)
#find_package(Qt6 REQUIRED COMPONENTS Core)


############### Sources ###############
add_subdirectory(src)

#set(PROJECT_SOURCES
#        src/main.cpp
#        src/mainwindow.cpp
#        src/mainwindow.h
#        src/mainwindow.ui
#        src/svg_handler.h
#        src/svg_handler.cpp
#        src/resources.qrc
#)

#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#    qt_add_executable(${PROJECT_NAME}
#        MANUAL_FINALIZATION
#        ${PROJECT_SOURCES}
#    )
#    else()
#        add_executable(${PROJECT_NAME}
#            ${PROJECT_SOURCES}
#        )
#endif()

#target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
##target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::SvgWidgets)
#target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Svg)
#target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
##target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::SvgWidgets)
##target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Svg)
##target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()


############### Testing ###############
add_subdirectory(test)
enable_testing()

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
#  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()


############### Visual Studio ###############
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})#Set Visualo Studio start-up project, so that one can directly run the debugger.
