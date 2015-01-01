
add_executable(test test.c)
install(TARGETS test DESTINATION bin)

include_directories(${PROJECT_SOURCE_DIR}/api)

target_link_libraries(test task)
