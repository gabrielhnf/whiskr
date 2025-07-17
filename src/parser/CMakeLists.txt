add_library(parser parser.cpp expression.cpp)

target_include_directories(parser
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
