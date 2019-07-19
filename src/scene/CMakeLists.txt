add_library(scene
  src/City.cpp
  src/GlobalIllumination.cpp)

target_include_directories(scene
  PRIVATE include/scene ${VL_INCLUDE_DIRS}
  PUBLIC include)

target_link_libraries(scene
  PRIVATE utils camera ${VL_LIBRARIES})
