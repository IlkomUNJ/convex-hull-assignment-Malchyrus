# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Komgraf_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Komgraf_autogen.dir\\ParseCache.txt"
  "Komgraf_autogen"
  )
endif()
