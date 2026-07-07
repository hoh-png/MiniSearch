set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(mini_search_benchmark
    benchmark_search.cpp
)

target_include_directories(mini_search_benchmark
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/query_engine
    ${CMAKE_SOURCE_DIR}/src/file_reader
    ${CMAKE_SOURCE_DIR}/src/text_processor
)

target_link_libraries(mini_search_benchmark
    PRIVATE
    benchmark::benchmark
    QueryParse
    FilePreproc
    TextProcessor
)

find_package(Threads REQUIRED)
target_link_libraries(mini_search_benchmark PRIVATE Threads::Threads)

target_compile_features(mini_search_benchmark PRIVATE cxx_std_17)

add_custom_command(TARGET mini_search_benchmark POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:QueryParse>"
        "$<TARGET_FILE_DIR:mini_search_benchmark>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:FilePreproc>"
        "$<TARGET_FILE_DIR:mini_search_benchmark>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:TextProcessor>"
        "$<TARGET_FILE_DIR:mini_search_benchmark>"
)