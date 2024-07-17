




#  building

1. go to libraries/glfw-3.4 and build (Release/Debug) glfw with parameters:
    `cmake -S . -B build -D CMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded`
2. go to libraries/portaudio and build it (Release/Debug)
    `cmake -S . -B build`
3. go to libraries/cimgui and build 
    `cmake -S . -B build -D CMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded`
4. generate glad/gl in https://gen.glad.sh/
    - header only option
    - opengl 3.3 extension version
3. go to libraries/cglm-0.9.4 and build 
    `cmake -S . -B build -D CMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded`
6. use premake in root directory to create vs project
    `premake5.exe vs2022`
