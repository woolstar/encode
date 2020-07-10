cmake_minimum_required( VERSION 3.10.0 )

add_library( encode-ascii85 STATIC
    asc85.c
    encode85.c
  )

generate_map( encode-ascii85 map85.pl )

target_include_directories( encode-ascii85 PUBLIC . )

add_executable( base85 base85.c )
target_link_libraries( base85 PUBLIC encode-ascii85 )
