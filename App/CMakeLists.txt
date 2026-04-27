cmake_minimum_required(VERSION 3.16)
project(App)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set Qt5 prefix path for macOS Homebrew
# set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/qt@5/5.15.18/")

file(GLOB_RECURSE ALL_SOURCES
    "*.cpp"
    "*.h"
    "*.qrc"
)

add_executable(App ${ALL_SOURCES})

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
target_link_libraries(App PRIVATE Qt5::Core Qt5::Widgets)

set(CTK_INSTALL_DIR "${PROJECT_SOURCE_DIR}/../CTK-install")
target_include_directories(App PRIVATE ${CTK_INSTALL_DIR}/include/ctk-0.1)
target_include_directories(App PRIVATE ${PROJECT_SOURCE_DIR}/../DatabaseManager)
target_link_libraries(App PRIVATE
    ${CTK_INSTALL_DIR}/lib/ctk-0.1/libCTKCore.dylib
    ${CTK_INSTALL_DIR}/lib/ctk-0.1/libCTKPluginFramework.dylib
)
