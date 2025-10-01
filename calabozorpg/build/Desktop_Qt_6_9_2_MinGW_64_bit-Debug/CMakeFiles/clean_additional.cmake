# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\calabozorpg_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\calabozorpg_autogen.dir\\ParseCache.txt"
  "calabozorpg_autogen"
  )
endif()
