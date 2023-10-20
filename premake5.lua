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

-- Include directories related to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Rexal/vendor/GLFW/include"
IncludeDir["Glad"] = "Rexal/vendor/Glad/include"
IncludeDir["ImGui"] = "Rexal/vendor/imgui"
IncludeDir["glm"] = "Rexal/vendor/glm"
IncludeDir["stb_image"] = "Rexal/vendor/stb_image"
IncludeDir["entt"] = "Rexal/vendor/entt/include"
IncludeDir["yaml_cpp"] = "Rexal/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "Rexal/vendor/ImGuizmo"

group "Dependencies"
	include "Rexal/vendor/GLFW"
	include "Rexal/vendor/Glad"
	include "Rexal/vendor/imgui"
	include "Rexal/vendor/yaml-cpp"
group ""

project "Rexal"
	location "Rexal"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "rxpch.h"
	pchsource "Rexal/src/rxpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"YAML_CPP_STATIC_DEFINE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}"
	}
	
	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib"
	}

	filter "files:Rexal/vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"RX_PLATFORM_WINDOWS",
			"RX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "RX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RX_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RX_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"Rexal/src",
		"Rexal/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Rexal"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RX_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "RX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "RX_DIST"
		runtime "Release"
		optimize "On"

project "Rexal-Editor"
	location "Rexal-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"Rexal/src",
		"Rexal/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"Rexal"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RX_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "RX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "RX_DIST"
		runtime "Release"
		optimize "On"