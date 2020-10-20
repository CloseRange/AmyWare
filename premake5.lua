workspace "AmyWare"
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "AmyWare/vendor/GLFW/include"
IncludeDir["Glad"] = "AmyWare/vendor/Glad/include"
IncludeDir["ImGui"] = "AmyWare/vendor/imgui"
IncludeDir["glm"] = "AmyWare/vendor/glm"

group "Dependencies"
	include "AmyWare/vendor/GLFW"
	include "AmyWare/vendor/Glad"
	include "AmyWare/vendor/imgui"
group ""

project "AmyWare"
	location "AmyWare"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "awpch.h"
	pchsource "AmyWare/src/awpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}
	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}
	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	filter "system:windows"
		systemversion "latest"

		defines {
			"AW_PLATFORM_WINDOWS",
			"AW_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "AW_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AW_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AW_DIST"
		runtime "Release"
		optimize "on"





project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs {
		"AmyWare/vendor/spdlog/include",
		"AmyWare/src",
		"AmyWare/vendor",
		"%{IncludeDir.glm}",
	}
	links {
		"AmyWare"
	}
	filter "system:windows"
		systemversion "latest"

		defines {
			"AW_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AW_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "AW_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "AW_DIST"
		runtime "Release"
		optimize "on"