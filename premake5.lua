workspace "Hazel"
    configurations { "Debug", "Release" }

project "Hazel"
    kind "SharedLib"
    language "C++"
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/Hazel/${cfg.buildcfg}"

    includedirs { "Hazel/vendor/spdlog/include" }

    files { "Hazel/**.h", "Hazel/**.hpp", "Hazel/**.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    
    defines { "HZ_PLATFORM_LINUX", "HZ_BUILD_LIB" }

project "Sandbox"
    kind "WindowedApp"
    language "C++"
    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/Sandbox/${cfg.buildcfg}"

    links { "Hazel" }

    includedirs { "Hazel/src" }

    files { "Sandbox/**.h", "Sandbox/**.hpp", "Sandbox/**.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    
    filter {}
    
    defines { "HZ_PLATFORM_LINUX" }