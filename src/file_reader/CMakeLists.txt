cmake_minimum_required(VERSION 3.16)
project(file_reader)

# 编译生成 FilePreproc.dll
add_library(FilePreproc SHARED
    file_reader.cpp
)

# DLL导出宏定义
target_compile_definitions(FilePreproc PRIVATE FILEPREPROC_EXPORTS)
# 对外暴露头文件目录（当前目录）
target_include_directories(FilePreproc PUBLIC .)
# 设置输出dll文件名严格为FilePreproc.dll
set_target_properties(FilePreproc PROPERTIES OUTPUT_NAME "FilePreproc")