cmake_minimum_required(VERSION 3.16)
project(DatabaseManager)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Sql)

set(CTK_INSTALL_DIR "${PROJECT_SOURCE_DIR}/../CTK-install")


file(GLOB_RECURSE ALL_SOURCES
    "*.cpp"
    "*.h"
    "*.qrc"
)
add_library(DatabaseManager SHARED ${ALL_SOURCES})

target_include_directories(DatabaseManager PRIVATE
    ${CTK_INSTALL_DIR}/include/ctk-0.1
)

target_link_libraries(DatabaseManager PRIVATE
    Qt5::Core
    Qt5::Sql
    ${CTK_INSTALL_DIR}/lib/ctk-0.1/libCTKCore.dylib
    ${CTK_INSTALL_DIR}/lib/ctk-0.1/libCTKPluginFramework.dylib
)

target_compile_definitions(DatabaseManager PRIVATE QT_PLUGIN)

set_target_properties(DatabaseManager PROPERTIES
    PREFIX ""
    OUTPUT_NAME "DatabaseManager"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/App/ctkPlugins"
)
