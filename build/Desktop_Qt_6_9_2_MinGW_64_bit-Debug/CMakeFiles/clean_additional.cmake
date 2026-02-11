# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Alexandria_autogen"
  "CMakeFiles\\Alexandria_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Alexandria_autogen.dir\\ParseCache.txt"
  )
endif()
