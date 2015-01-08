
add_executable(stream stream.cpp functions.cpp)
install(TARGETS stream DESTINATION bin)

add_executable(stream_par stream_par.cpp functions.cpp)
install(TARGETS stream_par DESTINATION bin)

add_executable(stream_par_for stream_par_for.cpp functions.cpp)
install(TARGETS stream_par_for DESTINATION bin)

include_directories($ENV{INTEL_TBB}/include)
include_directories(${PROJECT_SOURCE_DIR}/c++/api)

# Required for C++11 lambda expressions
set(CMAKE_CXX_FLAGS "-std=c++0x")

target_link_libraries(stream taskplus)
target_link_libraries(stream_par taskplus)
target_link_libraries(stream_par_for taskplus)
