cmake_minimum_required(VERSION 3.16)
project(query_engine)

# 编译生成 QueryParse.dll
add_library(QueryParse SHARED
    modules/query.cpp
)

# DLL导出宏定义
target_compile_definitions(QueryParse PRIVATE QUERY_PARSE_EXPORTS)
# 对外暴露headers文件夹，main主程序能#include "query.h"
target_include_directories(QueryParse PUBLIC headers)
# 设置输出dll文件名严格为QueryParse.dll
set_target_properties(QueryParse PROPERTIES OUTPUT_NAME "QueryParse")j
