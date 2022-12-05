project "KryptoImGui"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir("%{wks.location}/bin/" .. outputDir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-obj/" .. outputDir .. "/%{prj.name}")
	
	includeDir = {}
	includeDir["GLFW"]  = "%{wks.location}/KryptoImGui/vendor/submodules/GLFW/include"
	includeDir["Glad"]  = "%{wks.location}/KryptoImGui/vendor/submodules/Glad/include"
	includeDir["imgui"] = "%{wks.location}/KryptoImGui/vendor/submodules/imgui"
	includeDir["glm"]   = "%{wks.location}/KryptoImGui/vendor/submodules/glm"
	includeDir["boost"]   = "%{wks.location}/KryptoImGui/vendor/submodules/boost/include"
	includeDir["armadillo"] = "%{wks.location}/KryptoImGui/vendor/submodules/armadillo/include"

	files 
	{
		"src/**.cpp",
		"src/**.h",
		"vendor/submodules/glm/glm/**.hpp",
		"vendor/submodules/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"%{includeDir.GLFW}",
		"%{includeDir.Glad}",
		"%{includeDir.imgui}",
		"%{includeDir.glm}",
		"%{includeDir.boost}",
		"%{includeDir.armadillo}"
	}

	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
