
add_executable(testplus testplus.cpp)
install(TARGETS testplus DESTINATION bin)

include_directories($ENV{INTEL_TBB}/include)
include_directories(${PROJECT_SOURCE_DIR}/c++/api)

# Required for C++11 lambda expressions
set(CMAKE_CXX_FLAGS "-std=c++0x")

target_link_libraries(testplus taskplus)
