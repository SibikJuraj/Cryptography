project "GLFW"
	location ("../submodules/GLFW")
	kind "StaticLib"
	language "C"

	targetdir ("%{prj.location}/bin/" .. outputDir .. "/%{prj.name}")
	objdir ("%{prj.location}/bin-obj/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.location}/include/GLFW/glfw3.h",
		"%{prj.location}/include/GLFW/glfw3native.h",
		"%{prj.location}/src/glfw_config.h",
		"%{prj.location}/src/context.c",
		"%{prj.location}/src/init.c",
		"%{prj.location}/src/input.c",
		"%{prj.location}/src/monitor.c",
		"%{prj.location}/src/null_init.c",
		"%{prj.location}/src/null_joystick.c",
		"%{prj.location}/src/null_monitor.c",
		"%{prj.location}/src/null_window.c",
		"%{prj.location}/src/platform.c",
		"%{prj.location}/src/vulkan.c",
		"%{prj.location}/src/window.c"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"%{prj.location}/src/win32_init.c",
			"%{prj.location}/src/win32_joystick.c",
			"%{prj.location}/src/win32_module.c",
			"%{prj.location}/src/win32_monitor.c",
			"%{prj.location}/src/win32_time.c",
			"%{prj.location}/src/win32_thread.c",
			"%{prj.location}/src/win32_window.c",
			"%{prj.location}/src/wgl_context.c",
			"%{prj.location}/src/egl_context.c",
			"%{prj.location}/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

		links
		{
			"Dwmapi.lib"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
