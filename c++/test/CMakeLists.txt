
add_executable(testplus testplus.cpp)
install(TARGETS testplus DESTINATION bin)

include_directories($ENV{INTEL_TBB}/include)
include_directories(${PROJECT_SOURCE_DIR}/c++/api)

set(CMAKE_CXX_FLAGS "-std=c++0x")

target_link_libraries(testplus taskplus)
