add_library(mem_buffer_tmp SHARED mem_buffer_tmp.c)
target_link_libraries(mem_buffer_tmp)

add_library(mem_buffer STATIC mem_buffer.c)
target_link_libraries(mem_buffer)