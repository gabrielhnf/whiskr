add_library(helpers helpers.cpp)

target_include_directories(helpers
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
