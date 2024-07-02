workspace "Hazel"
    configurations { "Debug", "Release" }

project "Hazel"
    kind "SharedLib"
    language "C++"
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/Hazel/${cfg.buildcfg}"

    files { "Hazel/**.h", "Hazel/**.hpp", "Hazel/**.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "Sandbox"
    kind "WindowedApp"
    language "C++"
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/Sandbox/${cfg.buildcfg}"

    files { "Sandbox/**.h", "Sandbox/**.hpp", "Sandbox/**.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"