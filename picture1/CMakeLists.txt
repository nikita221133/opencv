cmake_minimum_required(VERSION 3.5)

project(untitled4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package (OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(untitled4 main.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

install(TARGETS untitled4
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
