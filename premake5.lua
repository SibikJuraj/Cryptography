workspace "Cryptography"
	architecture "x64"
	configurations { "Debug", "Release" }

	startproject "Cryptography"

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Cryptography/vendor/premakes/GLFW"
	include "Cryptography/vendor/premakes/Glad"
	include "Cryptography/vendor/premakes/imgui"
group ""

include "Cryptography"