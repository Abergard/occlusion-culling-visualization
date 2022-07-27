# Visualization of the Occlusion Culling method [![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/Abergard/occlusion-culling-visualization/tree/gitpod)

![](https://user-images.githubusercontent.com/5645572/60454151-68618f00-9c33-11e9-8785-83ad522bb8ee.gif)

## About
Occlusion Culling method deals with detection of invisible elements of scenes in order to eliminate them from the rendering process. This project aims to show how it works by draw objects in a few mode from first and third perspective. Both view can be enabled on demand.

![](https://user-images.githubusercontent.com/5645572/60455430-a0b69c80-9c36-11e9-9c8f-7efd37cfd11e.gif)

## Visualization options
![options](https://user-images.githubusercontent.com/5645572/60455617-22a6c580-9c37-11e9-826e-2219ae9fbbf8.png)

## Buildings (only Windows platform supported for now)
Firsty, you need to clone repository.
```
git clone --recursive https://github.com/Abergard/occlusion-culling-visualization.git
```

To build project the VisualizationLibrary need to be installed somewhere.
```
cd occlusion-culling-visualization/external/Visualization_Library
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DVL_GUI_WIN32_SUPPORT=ON -DVL_INSTALL_DATA=ON -DCMAKE_INSTALL_PREFIX=<path where want to install VisualizationLibrary>
cmake --build . --target install --config Release
```

To build main project pass install path to VL_ROOT from step before
``` 
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DVL_ROOT=<path to installed VisualizationLibrary> -DCMAKE_INSTALL_PREFIX=<path where want to install occlusion-culling-visualization> -Wno-dev
cmake --build . --target install --config Release
```

## Dev
To add and test new changes is highly recommended to build with Debug build type and OCV_TEST cmake's flag enabled.
```
cmake .. -DCMAKE_BUILD_TYPE=Debug -DOCV_TESTS=ON -DVL_ROOT=<path to installed VisualizationLibrary> -Wno-dev
cmake --build . --config Debug
ctest -V .
```

## Todo
There is a lot of work to do yet:
- [ ] Prepare code to run on linux
- [ ] Add basic tests
- [ ] Configure CI 
  - [ ] Appveyor
  - [ ] Travis
- [ ] Extend map/object loader to be able to load objects from blender.
- [ ] Add textures
- [ ] and many more...
