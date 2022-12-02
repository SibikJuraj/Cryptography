project "eigen"
	location ("../submodules/eigen")
	kind "StaticLib"
	language "C++"
		
	targetdir ("%{prj.location}/bin/" .. outputDir .. "/%{prj.name}")
	objdir ("%{prj.location}/bin-obj/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.location}/Eigen/.h**"
	}

	includedirs
	{
		"%{prj.location}/Eigen"
	}
		
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
