find_package(GLFW3 3.4 REQUIRED)

add_library(window
  src/Window.cpp
  # src/Win32Window.cpp
  src/GlfwWindow.cpp)

target_include_directories(window
  PRIVATE include/window ${VL_INCLUDE_DIRS}
  PUBLIC include)

target_link_libraries(window
  utils ${VL_LIBRARIES} glfw)


