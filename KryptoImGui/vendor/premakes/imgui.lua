project "imgui"
	location ("../submodules/imgui")
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{prj.location}/bin/" .. outputDir .. "/%{prj.name}")
	objdir ("%{prj.location}/bin-obj/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.location}/imconfig.h",
		"%{prj.location}/imgui.h",
		"%{prj.location}/imgui.cpp",
		"%{prj.location}/imgui_draw.cpp",
		"%{prj.location}/imgui_internal.h",
		"%{prj.location}/imgui_tables.cpp",
		"%{prj.location}/imgui_widgets.cpp",
		"%{prj.location}/imstb_rectpack.h",
		"%{prj.location}/imstb_textedit.h",
		"%{prj.location}/imstb_truetype.h",
		"%{prj.location}/imgui_demo.cpp",
		
		"%{prj.location}/implot.h",
		"%{prj.location}/implot_internal.h",
		"%{prj.location}/implot.cpp",
		"%{prj.location}/implot_items.cpp",
		"%{prj.location}/implot_demo.cpp"
	}