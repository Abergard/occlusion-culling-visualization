cmake_minimum_required(VERSION 3.10)

project("occlusion-culling-visualization" CXX)

set(CMAKE_CXX_STANDARD 17)

option(OCV_TESTS "Set to ON to build Occlusion Culling Visualization tests")

set(VL_ROOT "${CMAKE_SOURCE_DIR}/external/Visualization_Library_SDK"
  CACHE STRING "Visualization_Library SDK destination")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${VL_ROOT}/cmake")

# find_package(glfw3 3.3 REQUIRED)
find_package(Boost 1.6 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(VL COMPONENTS
  VLCore
  VLGraphics
  VLVG
  VLX
  VLVolume
  VLMolecule
  # VLWin32
  # VLGflw
  VLGLFW
  VLMain REQUIRED)

if(OCV_TESTS)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  add_subdirectory(external/googletest)
  enable_testing()
endif()

add_subdirectory(src)
