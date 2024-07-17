workspace "micro-daw"
    configurations { "Debug", "Release" }
    platforms { "Win64" }

project "micro-daw"
    kind "ConsoleApp"
    language "C"

    targetdir "bin/%{cfg.buildcfg}"
    files { "src/**.h", "src/**.c" }

    includedirs { "./libraries/glfw-3.4/include","./libraries/portaudio/include" }

    filter "configurations:Debug"
        libdirs { "./libraries/glfw-3.4/build/src/Debug","./libraries/portaudio/build/Debug"  }
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        libdirs { "./libraries/glfw-3.4/build/src/Release","./libraries/portaudio/build/Release"  }
        defines { "NDEBUG" }
        optimize "On"

    filter {}
        links { "portaudio_static_x64" }
        links { "glfw3" }



