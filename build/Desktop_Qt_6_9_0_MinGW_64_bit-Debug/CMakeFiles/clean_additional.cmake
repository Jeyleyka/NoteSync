# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\NoteSync_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\NoteSync_autogen.dir\\ParseCache.txt"
  "NoteSync_autogen"
  )
endif()
