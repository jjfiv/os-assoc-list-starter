add_executable(main main.c bytes.c assoc_list.c)
add_executable(test_bytes test_bytes.c bytes.c)
add_executable(test_assoc test_assoc.c assoc_list.c bytes.c)
