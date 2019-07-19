add_library(camera
  src/DoubleCamera.cpp
  src/Observator.cpp
  src/Player.cpp)

target_include_directories(camera
  PRIVATE include/camera ${VL_INCLUDE_DIRS}
  PUBLIC include)

target_link_libraries(camera
  PRIVATE utils ${VL_LIBRARIES}
  PUBLIC window)
