project "Cryptography"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir("%{wks.location}/bin/" .. outputDir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-obj/" .. outputDir .. "/%{prj.name}")
	
	includeDir = {}
	includeDir["GLFW"]  = "%{wks.location}/Cryptography/vendor/submodules/GLFW/include"
	includeDir["Glad"]  = "%{wks.location}/Cryptography/vendor/submodules/Glad/include"
	includeDir["imgui"] = "%{wks.location}/Cryptography/vendor/submodules/imgui"
	includeDir["glm"]   = "%{wks.location}/Cryptography/vendor/submodules/glm"
	includeDir["boost"]   = "%{wks.location}/Cryptography/vendor/submodules/boost/include"
	includeDir["MatrixLib"] = "%{wks.location}/Cryptography/vendor/submodules/MatrixLib"
	includeDir["ImGuiFileDialog"] = "%{wks.location}/Cryptography/vendor/submodules/ImGuiFileDialog"
	files 
	{
		"src/**.cpp",
		"src/**.h",
		"vendor/submodules/glm/glm/**.hpp",
		"vendor/submodules/glm/glm/**.inl",
		"vendor/submodules/ImGuiFileDialog/ImGuiFileDialog.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
	}

	includedirs
	{
		"src",
		"%{includeDir.GLFW}",
		"%{includeDir.Glad}",
		"%{includeDir.imgui}",
		"%{includeDir.glm}",
		"%{includeDir.boost}",
		"%{includeDir.MatrixLib}",
		"%{includeDir.ImGuiFileDialog}",
	}

	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib",
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
