#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "zstd::libzstd_static" for configuration "RelWithDebInfo"
set_property(TARGET zstd::libzstd_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(zstd::libzstd_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/zstd_static.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS zstd::libzstd_static )
list(APPEND _IMPORT_CHECK_FILES_FOR_zstd::libzstd_static "${_IMPORT_PREFIX}/lib/zstd_static.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
