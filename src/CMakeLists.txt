cmake_minimum_required(VERSION 3.2)
project(file_system_impl)

add_subdirectory(fs)
set(SOURCE_FILES main.cpp)

add_executable(file_system_impl ${SOURCE_FILES})
target_link_libraries(file_system_impl fs)
install(TARGETS file_system_impl DESTINATION ${FSIMPL_INSTALL_BIN_DIR})