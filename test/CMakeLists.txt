cmake_minimum_required(VERSION 3.2)
project(file_system_impl_tests)

add_subdirectory(lib/googletest)

include_directories(${FS_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES ut_fs.cpp src/ut_fs.h)

add_executable(file_system_impl_tests ${SOURCE_FILES})
target_link_libraries(file_system_impl_tests fs gtest)
install(TARGETS file_system_impl_tests DESTINATION bin)
