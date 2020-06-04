workspace "AmyWare"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


IncludeDir = {}
IncludeDir["GLFW"] = "AmyWare/vendor/GLFW/include"
include "AmyWare/vendor/GLFW"


project "AmyWare"
	location "AmyWare"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "awpch.h"
	pchsource "AmyWare/src/awpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	links {
		"GLFW",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"AW_PLATFORM_WINDOWS",
			"AW_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	filter "configurations:Debug"
		defines "AW_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AW_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "AW_DIST"
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
		"AmyWare/vendor/spdlog/include",
		"AmyWare/src"
	}

	links {
		"AmyWare"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"AW_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "AW_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AW_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "AW_DIST"
		optimize "On"