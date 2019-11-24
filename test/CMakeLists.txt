cmake_minimum_required( VERSION 3.10.0 )

add_executable( test_asci test_asci.c )
target_link_libraries( test_asci PUBLIC encode-ascii85 )

