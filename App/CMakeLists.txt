cmake_minimum_required(VERSION 3.16)
project(App)
file(GLOB_RECURSE ALL_SOURCES
    "*.cpp"
    "*.h"
    "*.qrc"
)
set(CMAKE_AUTOMOC ON)   # 处理信号槽
set(CMAKE_AUTORCC ON)   # 处理 .qrc 资源文件（解决你现在的错误！）

add_executable(App ${ALL_SOURCES})

# 链接 Qt
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
target_link_libraries(App PRIVATE Qt5::Core Qt5::Widgets)

# CTK
set(CTK_DIR "${PROJECT_SOURCE_DIR}/../3rdpty")
target_include_directories(App PRIVATE ${CTK_DIR}/include/ctk-0.1)
target_link_libraries(App PRIVATE
    ${CTK_DIR}/lib/ctk-0.1/libCTKCore.a
    ${CTK_DIR}/lib/ctk-0.1/libCTKPluginFramework.a
)

if(WIN32)
    # Resolve windeployqt next to the Qt5Core runtime selected by CMake.
    get_target_property(QT5_CORE_DLL Qt5::Core IMPORTED_LOCATION_DEBUG)
    if(NOT QT5_CORE_DLL)
        get_target_property(QT5_CORE_DLL Qt5::Core IMPORTED_LOCATION_RELEASE)
    endif()
    if(NOT QT5_CORE_DLL)
        get_target_property(QT5_CORE_DLL Qt5::Core IMPORTED_LOCATION)
    endif()

    if(QT5_CORE_DLL)
        get_filename_component(QT_BIN_DIR "${QT5_CORE_DLL}" DIRECTORY)
        set(WINDEPLOYQT_EXECUTABLE "${QT_BIN_DIR}/windeployqt.exe")

        if(EXISTS "${WINDEPLOYQT_EXECUTABLE}")
            add_custom_command(TARGET App POST_BUILD
                COMMAND "${WINDEPLOYQT_EXECUTABLE}"
                        --verbose 0
                        "$<TARGET_FILE:App>"
                COMMENT "Deploying Qt runtime for App.exe"
            )
        else()
            message(WARNING "windeployqt not found: ${WINDEPLOYQT_EXECUTABLE}")
        endif()
    else()
        message(WARNING "Unable to resolve Qt5Core runtime path for deployment")
    endif()
endif()