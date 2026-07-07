cmake_minimum_required(VERSION 3.16)
project(text_processor)

# 编译生成 TextProcessor.dll
add_library(TextProcessor SHARED
    text_processor.cpp
)

# DLL导出宏定义
target_compile_definitions(TextProcessor PRIVATE TEXTPROCESSOR_EXPORTS)
# 对外暴露头文件目录（当前目录）
target_include_directories(TextProcessor PUBLIC .)
# 设置输出dll文件名严格为TextProcessor.dll
set_target_properties(TextProcessor PROPERTIES OUTPUT_NAME "TextProcessor")