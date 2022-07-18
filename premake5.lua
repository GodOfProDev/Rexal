workspace "Rexal"
	architecure "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecure}"
project "Rexal"
	location "Rexal"
	kind "SharedLib"
	language"C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	targetdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"{prj.name}/src/**.h",
		"{prj.name}/src/**.cpp"
	}
	
	include
	{
		"{prj.name}/vendor/spdlog/include"
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
			("{COPY} %{cfg.buildtarger.relpath} ../bin/" .. outputdir .. "/Sandbox)
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