workspace "Rexal"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Rexal"
	location "Rexal"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "rxpch.h"
	pchsource "Rexal/src/rxpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RX_PLATFORM_WINDOWS",
			"RX_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "RX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RX_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Rexal/vendor/spdlog/include",
		"Rexal/src"
	}

	links
	{
		"Rexal"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RX_DIST"
		optimize "On"