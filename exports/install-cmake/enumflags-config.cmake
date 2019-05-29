if(TARGET EnumFlags::EnumFlags)
  return()
endif()

add_library(EnumFlags::EnumFlags INTERFACE IMPORTED)
set_target_properties(
  EnumFlags::EnumFlags
  PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "/home/arhipov_d/dev/1/enum-flags/tmp/stage/include"
)
