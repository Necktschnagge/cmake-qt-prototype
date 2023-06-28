file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp *.ui *.qrc)

#add_executable(${PROJECT_NAME} ${SOURCES})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${SOURCES}
    )
    else()
        add_executable(${PROJECT_NAME}
            ${SOURCES}
        )
endif()

############### Libraries ###############
if(LINUX)
	target_link_libraries(${PROJECT_NAME} PUBLIC
		pthread
	)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
##target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::SvgWidgets)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Svg)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Core)

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES}) #for using in tests
target_link_libraries(${PROJECT_NAME}_lib PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME}_lib PUBLIC Qt${QT_VERSION_MAJOR}::Svg)
target_link_libraries(${PROJECT_NAME}_lib PUBLIC Qt${QT_VERSION_MAJOR}::Core)
