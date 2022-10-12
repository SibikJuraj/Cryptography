project "Glad"
	location ("../submodules/Glad")
	kind "StaticLib"
	language "C"
		
	targetdir ("%{prj.location}/bin/" .. outputDir .. "/%{prj.name}")
	objdir ("%{prj.location}/bin-obj/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.location}/include/glad/glad.h",
		"%{prj.location}/include/KHR/khrplatform.h",
		"%{prj.location}/src/glad.c"
	}

	includedirs
	{
		"%{prj.location}/include"
	}
		
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
