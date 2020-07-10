cmake_minimum_required( VERSION 3.10.0 )

project ( w-encode CXX C )
set ( CMAKE_CXX_STANDARD 17 )

function ( generate_map target generator )
  get_filename_component( _base ${generator} NAME_WE )

  message( STATUS "generating character map for ${target} from ${generator} to ${_base}.h" )

  add_custom_target ( "map-${target}"
    DEPENDS ${generator}
    COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/${generator}" "${CMAKE_CURRENT_BINARY_DIR}/${_base}.h"
    )

  target_include_directories( ${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} )
  add_dependencies( ${target} "map-${target}" )

endfunction()

add_subdirectory( "ascii85" )
add_subdirectory( "alpha71" )
add_subdirectory( "test" )

enable_testing ()
add_test( NAME test-ascii COMMAND test/test_asci )
add_test( NAME test-alpha COMMAND test/test_alpha )

