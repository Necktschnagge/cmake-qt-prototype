file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)



############### Target via add_executable ###############
add_executable(${TEST_PROJECT_NAME} ${TEST_SOURCES})



############### Test via add_test ###############
add_test(NAME ${TEST_PROJECT_NAME} COMMAND ${TEST_PROJECT_NAME}) # what does command mean in detail?



############### Libraries via target_link_libraries ###############
if(LINUX)
	target_link_libraries(${TEST_PROJECT_NAME} PUBLIC
		pthread
	)
endif()
target_link_libraries(${TEST_PROJECT_NAME} PUBLIC ${PROJECT_NAME_LIB} gtest)
