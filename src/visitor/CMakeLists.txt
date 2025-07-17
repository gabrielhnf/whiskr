add_library(visitor visitor.cpp)

target_include_directories(visitor
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
