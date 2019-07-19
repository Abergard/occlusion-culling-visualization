add_library(utils
  src/FileAccess.cpp
  src/StandardFileAccess.cpp
  src/BuildingLoader.cpp
  src/XmlBuildingLoader.cpp
  src/FpsCounter.cpp
  src/OcclusionStatistics.cpp)

target_include_directories(utils
  PRIVATE include/utils ${VL_INCLUDE_DIRS}
  PUBLIC include)

target_link_libraries(utils
  PRIVATE Boost::boost ${VL_LIBRARIES})

if(OCV_TESTS)
add_executable(utils-ut
  src/StandardFileAccess.ut.cpp
  src/XmlBuildingLoader.ut.cpp)
target_include_directories(utils-ut
  PRIVATE include/utils)
target_link_libraries(utils-ut
  PRIVATE utils gtest_main gmock)
  add_test(utils-ut ${CMAKE_BINARY_DIR}/src/utils/utils-ut --gtest_color=yes)
endif()
