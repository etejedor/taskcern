
add_library(taskmanager SHARED taskmanager.cpp taskbackend.cpp)
install(TARGETS taskmanager DESTINATION lib)
install(FILES taskmanager.h taskbackend.h DESTINATION include)

include_directories($ENV{INTEL_TBB}/include)

find_library(LIBTBB tbb HINTS $ENV{INTEL_TBB}/lib/intel64/gcc4.4)
if(NOT LIBTBB)
  message(FATAL_ERROR "Library tbb not found in $ENV{INTEL_TBB}/lib/intel64/gcc4.4")
endif()

target_link_libraries(taskmanager ${LIBTBB})

