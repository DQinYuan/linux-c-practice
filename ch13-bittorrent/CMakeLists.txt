aux_source_directory(. SRC_LIST)
add_executable(ttorrent ${SRC_LIST})
add_compile_definitions(DEBUG)