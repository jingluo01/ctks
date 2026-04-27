cmake_minimum_required(VERSION 3.16)
project(CTKSTUDY)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt5 路径（Homebrew）
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")
find_package(Qt5 REQUIRED COMPONENTS Core)

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(DatabaseManager)
add_subdirectory(App)
