cmake_minimum_required(VERSION 4.0.3)
project(whiskr)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src/utils)
add_subdirectory(src/lexer)
add_subdirectory(src/parser)
add_subdirectory(src/visitor)

add_executable(visitor_example examples/visitor/main.cpp)

target_link_libraries(visitor_example
    visitor
    parser
    helpers
    types
)

add_executable(parser_example examples/parser/main.cpp)

target_link_libraries(parser_example
    parser
    visitor
    helpers
    types
)

add_executable(lexer_example examples/lexer/main.cpp)

target_link_libraries(lexer_example
    helpers
    types
    )
