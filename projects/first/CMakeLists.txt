cmake_minimum_required(VERSION 2.6)
project(first)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(first_SRCS first.cpp main.cpp)

qt4_automoc(${first_SRCS})
add_executable(first ${first_SRCS})
target_link_libraries(first ${QT_QTCORE_LIBRARY})

install(TARGETS first RUNTIME DESTINATION bin)
