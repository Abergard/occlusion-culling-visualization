add_library(input
  src/VlController.cpp
  src/WholeApplicationVlController.cpp
  src/ToggleOcvAlgorithm.cpp
  src/ToggleVisualizationEffect.cpp
  src/ToggleWireMode.cpp
  src/TogglePlayerAABBDraw.cpp
  src/ToggleObserverAABBDraw.cpp
  src/ToggleActiveView.cpp
  src/ToggleEditorMode.cpp
  src/ToggleSecondView.cpp
  src/ToggleMenu.cpp
  src/ToggleView.cpp
  src/ExitApplication.cpp)

target_include_directories(input
  PRIVATE include/input
  PUBLIC include ${VL_INCLUDE_DIRS})

target_link_libraries(input
  PRIVATE view)
