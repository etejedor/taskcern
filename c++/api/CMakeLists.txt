
add_library(taskplus SHARED taskplus.cpp)

install(TARGETS taskplus DESTINATION lib)
install(FILES taskplus.h DESTINATION include)

include_directories($ENV{INTEL_TBB}/include)

find_library(LIBTBB tbb HINTS $ENV{INTEL_TBB}/lib/intel64/gcc4.4)
if(NOT LIBTBB)
  message(FATAL_ERROR "Library tbb not found in $ENV{INTEL_TBB}/lib/intel64/gcc4.4")
endif()

target_link_libraries(taskplus ${LIBTBB})

