




#  building

1. go to libraries/glfw-3.4 and build (Release/Debug) glfw with parameters:
    `cmake -S . -B build -D CMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded`
2. go to libraries/portaudio and build it (Release/Debug)
    `cmake -S . -B build`
3. go to libraries/cimgui and build 
    `cmake -S . -B build -D CMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded`
5. use premake in root directory to create vs project
    `premake5.exe vs2022`
