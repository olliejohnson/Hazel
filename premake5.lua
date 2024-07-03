workspace "Hazel"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["GLAD"] = "Hazel/vendor/GLAD/include"
IncludeDir["imgui"] = "Hazel/vendor/imgui"

include "Hazel/vendor/GLFW"
include "Hazel/vendor/GLAD"
include "Hazel/vendor/imgui"

project "Hazel"
	location "Hazel"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imgui}"
	}

	links {
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_LIB",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines {
			"HZ_DEBUG",
			"HZ_ENABLE_ASSERTS"
		}

		buildoptions "/MDd"

		symbols "On"

	filter "configurations:Release"
		defines {
			"HZ_RELEASE"
		}

		buildoptions "/MD"

		optimize "On"

	filter "configurations:Dist"
		defines {
			"HZ_DIST"
		}

		buildoptions "/MD"

		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Hazel/vendor/spdlog/include",
		"Hazel/src"
	}

	links {
		"Hazel"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines {
			"HZ_DEBUG"
		}

		buildoptions "/MDd"

		symbols "On"

	filter "configurations:Release"
		defines {
			"HZ_RELEASE"
		}

		buildoptions "/MD"

		optimize "On"

	filter "configurations:Dist"
		defines {
			"HZ_DIST"
		}

		buildoptions "/MD"

		optimize "On"