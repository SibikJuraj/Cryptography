workspace "KryptoImGui"
	architecture "x64"
	configurations { "Debug", "Release" }

	startproject "KryptoImGui"

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "KryptoImGui/vendor/premakes/GLFW"
	include "KryptoImGui/vendor/premakes/Glad"
	include "KryptoImGui/vendor/premakes/imgui"
group ""

include "KryptoImGui"