
add_library(task SHARED task.cpp)

install(TARGETS task DESTINATION lib)
install(FILES task.h DESTINATION include)

include_directories(${PROJECT_SOURCE_DIR}/manager)

target_link_libraries(task taskmanager)

