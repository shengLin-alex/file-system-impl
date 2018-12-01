cmake_minimum_required(VERSION 3.2)
project(fs C CXX)

set(SOURCE_FILES
        file.h
        find_link_visitor.cpp
        find_link_visitor.h
        find_node_by_pathname_visitor.cpp
        find_node_by_pathname_visitor.h
        find_visitor.cpp
        find_visitor.h
        folder.h
        info_content_visitor.cpp
        info_content_visitor.h
        link.h
        node.h
        node_builder.h
        node_iterator.h
        node_visitor.h
        null_iterator.h)

add_library(fs SHARED STATIC ${SOURCE_FILES})

install(TARGETS fs DESTINATION ${FSIMPL_INSTALL_LIB_DIR})
install(FILES
        file.h
        find_link_visitor.h
        find_node_by_pathname_visitor.h
        find_visitor.h folder.h
        info_content_visitor.h
        link.h
        node.h
        node_builder.h
        node_iterator.h
        node_visitor.h
        null_iterator.h
        DESTINATION ${FSIMPL_INSTALL_INCLUDE_DIR})