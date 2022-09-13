# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\slideshow_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\slideshow_autogen.dir\\ParseCache.txt"
  "slideshow_autogen"
  )
endif()
