cmake_minimum_required(VERSION 3.18)

project(QtStopWatches LANGUAGES CXX)

# Find Qt5 package
find_package(Qt5 COMPONENTS Widgets REQUIRED)

if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

# Tell CMake to run moc, uic, and rcc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Set up the source files for the project
set(SOURCES
    main.cpp
    mainwindow.cpp
    LCDStopWatch.cpp
)

# Set up the header files for the project
set(HEADERS
    mainwindow.h
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

# Add an executable target for the project
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link Qt5 libraries to the target
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_BUILD_TYPE STREQUAL "Release" AND WIN32)
  set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
endif()
