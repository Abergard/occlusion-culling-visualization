add_library(renderer
  src/AABBRenderer.cpp
  src/GuiRenderer.cpp
  src/ObservatorRenderer.cpp
  src/PlayerRenderer.cpp)

target_include_directories(renderer
  PRIVATE include/renderer ${VL_INCLUDE_DIRS}
  PUBLIC include)

target_link_libraries(renderer
  PRIVATE utils # scene
  GL
  ${VL_LIBRARIES})
