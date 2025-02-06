#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Folly::folly" for configuration "RelWithDebInfo"
set_property(TARGET Folly::folly APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Folly::folly PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/folly.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Folly::folly )
list(APPEND _IMPORT_CHECK_FILES_FOR_Folly::folly "${_IMPORT_PREFIX}/lib/folly.lib" )

# Import target "Folly::folly_test_util" for configuration "RelWithDebInfo"
set_property(TARGET Folly::folly_test_util APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Folly::folly_test_util PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/folly_test_util.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Folly::folly_test_util )
list(APPEND _IMPORT_CHECK_FILES_FOR_Folly::folly_test_util "${_IMPORT_PREFIX}/lib/folly_test_util.lib" )

# Import target "Folly::follybenchmark" for configuration "RelWithDebInfo"
set_property(TARGET Folly::follybenchmark APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Folly::follybenchmark PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/follybenchmark.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Folly::follybenchmark )
list(APPEND _IMPORT_CHECK_FILES_FOR_Folly::follybenchmark "${_IMPORT_PREFIX}/lib/follybenchmark.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
