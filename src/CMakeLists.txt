############### Find Source Files ###############
file(GLOB_RECURSE ALL_SOURCE_FILES LIST_DIRECTORIES true *.h *.cpp *.ui)



############### Target via add_executable ###############
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${ALL_SOURCE_FILES})
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
	if(ANDROID)
		add_library(${PROJECT_NAME} SHARED ${ALL_SOURCE_FILES})
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
	else()
		add_executable(${PROJECT_NAME} ${ALL_SOURCE_FILES})
	endif()
endif()



############### Libraries via target_link_libraries ###############
if(USE_QT6)
    target_link_libraries(${PROJECT_NAME} PRIVATE
	Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Svg
	Qt${QT_VERSION_MAJOR}::SvgWidgets
	)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE 
	Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Svg
	)
endif()
if(LINUX)
	target_link_libraries(${PROJECT_NAME} PUBLIC
		pthread
	)
endif()



############### Target Properties ###############
set_target_properties(${PROJECT_NAME} PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)



install(TARGETS ${PROJECT_NAME}
	BUNDLE DESTINATION .
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)



############### Target Finalize ###############
if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(${PROJECT_NAME})
endif()



############### Target via add_library ###############
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_library(${PROJECT_NAME_LIB} STATIC MANUAL_FINALIZATION ${ALL_SOURCE_FILES})
else()
	add_library(${PROJECT_NAME_LIB} STATIC ${ALL_SOURCE_FILES}) #for using in tests
endif()



############### Libraries via target_link_libraries ###############
if(USE_QT6)
    target_link_libraries(${PROJECT_NAME_LIB} PRIVATE
	Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Svg
	Qt${QT_VERSION_MAJOR}::SvgWidgets
	)
else()
    target_link_libraries(${PROJECT_NAME_LIB} PRIVATE 
	Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Svg
	)
endif()
if(LINUX)
	target_link_libraries(${PROJECT_NAME_LIB} PUBLIC
		pthread
	)
endif()



############### Target Properties ###############
set_target_properties(${PROJECT_NAME_LIB} PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)



install(TARGETS ${PROJECT_NAME_LIB}
	BUNDLE DESTINATION .
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)



############### Target Finalize ###############
if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(${PROJECT_NAME_LIB})
endif()
