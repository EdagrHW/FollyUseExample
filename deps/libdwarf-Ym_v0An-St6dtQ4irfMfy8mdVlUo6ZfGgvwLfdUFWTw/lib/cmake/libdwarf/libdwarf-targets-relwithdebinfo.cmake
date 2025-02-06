#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libdwarf::dwarf" for configuration "RelWithDebInfo"
set_property(TARGET libdwarf::dwarf APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(libdwarf::dwarf PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "C"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/dwarf.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS libdwarf::dwarf )
list(APPEND _IMPORT_CHECK_FILES_FOR_libdwarf::dwarf "${_IMPORT_PREFIX}/lib/dwarf.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
