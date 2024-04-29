add_library(sample_rand_lib OBJECT
    random.c
)

target_include_directories(sample_rand_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)