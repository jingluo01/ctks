cmake_minimum_required(VERSION 3.16)
project(DatabaseManager)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Sql)

add_library(DatabaseManager SHARED
    DatabaseManagerImp.h
    DatabaseManagerImp.cpp
    DatabaseManager.qrc
)

target_include_directories(DatabaseManager PRIVATE
    ${PROJECT_SOURCE_DIR}/../3rdpty/include/ctk-0.1
)

target_link_libraries(DatabaseManager PRIVATE
    Qt5::Core
    Qt5::Sql
    ${PROJECT_SOURCE_DIR}/../3rdpty/lib/ctk-0.1/libCTKCore.a
    ${PROJECT_SOURCE_DIR}/../3rdpty/lib/ctk-0.1/libCTKPluginFramework.a
)

target_compile_definitions(DatabaseManager PRIVATE QT_PLUGIN)

set_target_properties(DatabaseManager PROPERTIES
    PREFIX ""
    OUTPUT_NAME "DatabaseManager"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/ctkPlugins"
)
