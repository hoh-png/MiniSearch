cmake_minimum_required(VERSION 3.16)
project(query_engine)

# 编译生成 QueryParse.dll
add_library(QueryParse SHARED
    query_engine.cpp
)

# DLL导出宏定义
target_compile_definitions(QueryParse PRIVATE QUERY_PARSE_EXPORTS)
# 对外暴露头文件目录（当前目录）
target_include_directories(QueryParse PUBLIC .)
# 设置输出dll文件名严格为QueryParse.dll
set_target_properties(QueryParse PROPERTIES OUTPUT_NAME "QueryParse")