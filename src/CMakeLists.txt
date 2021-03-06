add_subdirectory(utils)
add_subdirectory(window)
add_subdirectory(renderer)
add_subdirectory(camera)
add_subdirectory(scene)
add_subdirectory(gui)
add_subdirectory(view)
add_subdirectory(input)

option(Win32App "ON - windows application, OFF - console application" ON)

if(Win32App)
  add_executable(occlusion-culling-visualization WIN32
    VlWinWin32Ocv.cpp
    )
else()
  add_executable(occlusion-culling-visualization
    VlWinConsoleOcv.cpp
    )
endif()

target_include_directories(occlusion-culling-visualization
  PRIVATE ${VL_INCLUDE_DIRS})

target_link_libraries(occlusion-culling-visualization
  PRIVATE ${VL_LIBRARIES} ${OPENGL_LIBRARIES}
          camera utils window view input)

target_compile_options(occlusion-culling-visualization
  PRIVATE /W4)
  
install (TARGETS occlusion-culling-visualization
  RUNTIME DESTINATION ./bin
  COMPONENT OCVexe)

install(FILES
  ${PROJECT_SOURCE_DIR}/data/city.tmx
  DESTINATION ./data
  COMPONENT MAPS)

install(DIRECTORY
  ${PROJECT_SOURCE_DIR}/external/Visualization_Library/data/font
  DESTINATION ./data
  COMPONENT DATA)

install(FILES
  ${VL_ROOT}/bin/VLCore.dll
  ${VL_ROOT}/bin/VLGraphics.dll
  ${VL_ROOT}/bin/VLVG.dll
  ${VL_ROOT}/bin/VLX.dll
  ${VL_ROOT}/bin/VLVolume.dll
  ${VL_ROOT}/bin/VLMolecule.dll
  ${VL_ROOT}/bin/VLWin32.dll
  ${VL_ROOT}/bin/VLMain.dll
  DESTINATION ./bin
  COMPONENT VLDLL)

set(CPACK_PACKAGE_NAME "OcclusionCullingVisualizationInstaller")
set(CPACK_PACKAGE_VENDOR "Abergard")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Occlusion installer")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "OcclusionCullingVisualization")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")

include(CPack)

cpack_add_component(OCVexe
  DISPLAY_NAME "Occlusion Culling Visualization"
  DESCRIPTION "Occlusion Culling Visualization"
  HIDDEN)

cpack_add_component(MAPS
  DISPLAY_NAME "Maps"
  DESCRIPTION "Set of city maps"
  HIDDEN)

cpack_add_component(DATA
  DISPLAY_NAME "Data"
  DESCRIPTION "Sef of additional data like fonts"
  HIDDEN)

cpack_add_component_group(OCVDLL
  DISPLAY_NAME "DLL-s"
  DESCRIPTION "Set of dll needed to run this applications")

cpack_add_component(VLDLL
  DISPLAY_NAME "VL"
  DESCRIPTION "Set of Visualization Library DLL-s"
  GROUP OCVDLL)
