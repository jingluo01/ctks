cmake_minimum_required(VERSION 3.16)
project(CTKSTUDY)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========== Qt 自动 MOC 必须打开 ==========
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 找 Qt5

set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.12.12/5.12.12/mingw73_64")
set(Qt5_DIR "C:/Qt/Qt5.12.12/5.12.12/mingw73_64/lib/cmake/Qt5" CACHE PATH "Qt5 CMake package path" FORCE)
set(Qt5Core_DIR "C:/Qt/Qt5.12.12/5.12.12/mingw73_64/lib/cmake/Qt5Core" CACHE PATH "Qt5Core CMake package path" FORCE)
set(Qt5Gui_DIR "C:/Qt/Qt5.12.12/5.12.12/mingw73_64/lib/cmake/Qt5Gui" CACHE PATH "Qt5Gui CMake package path" FORCE)
set(Qt5Widgets_DIR "C:/Qt/Qt5.12.12/5.12.12/mingw73_64/lib/cmake/Qt5Widgets" CACHE PATH "Qt5Widgets CMake package path" FORCE)
find_package(Qt5 REQUIRED COMPONENTS Core)

# 包含头文件路径（让 App 能找到 DatabaseManager 里的接口）
include_directories(${PROJECT_SOURCE_DIR})

# 构建子模块
add_subdirectory(DatabaseManager)  
add_subdirectory(App)