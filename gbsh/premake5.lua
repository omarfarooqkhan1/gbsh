project "gbsh"
	location "../build/%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	toolset "gcc"
	cppdialect "C++17"
	staticruntime "on"
	targetdir ("../bin/%{prj.name}/%{cfg.buildcfg}")
	objdir ("../bin-init/%{prj.name}/%{cfg.buildcfg}")
	files{
		"include/**.h",
		"include/**.hpp",
		"src/**.cc",
		"src/**.cpp"
	}
	includedirs{
		"include"
	}
	filter "configurations:Debug"
		defines {"DEBUG"} 
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines {"NDEBUG"} 
		optimize "on"
		runtime "Release"

