workspace "micro-daw"
    configurations { "Debug", "Release" }
    platforms { "Win64" }

project "micro-daw"
    kind "ConsoleApp"
    language "C"
    staticruntime "on"

    targetdir "bin/%{cfg.buildcfg}"
    files { "src/**.h", "src/**.c" }

    includedirs { "./libraries/glfw-3.4/include",
                  "./libraries/portaudio/include",
                  "./libraries/cimgui",
                  "./libraries/glad-include" }

    filter "configurations:Debug"
        libdirs { "./libraries/glfw-3.4/build/src/Debug",
                  "./libraries/cimgui/build/Debug",
                  "./libraries/portaudio/build/Debug"  }
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        libdirs { "./libraries/glfw-3.4/build/src/Release",
                  "./libraries/cimgui/build/Release",
                  "./libraries/portaudio/build/Release"  }
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"

    filter {}
        links { "portaudio_static_x64" }
        links { "glfw3" }
        links { "cimgui" }



