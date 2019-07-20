add_library(gui
  src/Menu.cpp
  src/InformationMenu.cpp)

target_include_directories(gui
  PRIVATE include/gui ${VL_INCLUDE_DIRS}
  PUBLIC include)

target_link_libraries(gui
  PUBLIC camera utils view
  PRIVATE renderer
  ${VL_LIBRARIES})
