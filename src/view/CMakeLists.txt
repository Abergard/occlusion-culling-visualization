add_library(view
  src/VisualizationView.cpp)

target_include_directories(view
  PRIVATE include/view ${VL_INCLUDE_DIRS}
  PUBLIC include)

target_link_libraries(view
  PUBLIC camera utils scene gui
  PRIVATE renderer ${VL_LIBRARIES})
