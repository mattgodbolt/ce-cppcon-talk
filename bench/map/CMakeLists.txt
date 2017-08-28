set(SOURCE_FILES MapBench.cpp OrderIdMap.h)
add_executable(map_bench ${SOURCE_FILES})
target_link_libraries(map_bench benchmark)