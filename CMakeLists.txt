cmake_minimum_required(VERSION 3.16)
project(APerioditile)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 查找 Qt 库
find_package(Qt6 COMPONENTS Core Gui Widgets Charts Svg SvgWidgets REQUIRED)

# 自动处理 MOC、UIC 和 RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 添加可执行文件
add_executable(${PROJECT_NAME}
    main.cpp
    tilinggenerator.cpp
    customtiledetector.cpp
    mathanalysistool.cpp
    artcreationexporter.cpp
)

# 链接 Qt 库
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Charts
    Qt6::Svg
    Qt6::SvgWidgets
)