solution "gmsv_libnoise"

	language "C++"
	location ( "projects/" .. os.get() )
	flags { "Symbols", "NoEditAndContinue", "NoPCH", "EnableSSE" }
	targetdir ( "builds/" .. os.get() .. "/" )
	includedirs { 
		"include/",
		"lib/"
	}
	files {
		"lib/noise/**.*",
		"src/**.*"
	}

	targetname ("gmsv_libnoise")
	if (os.is("windows")) then
		targetsuffix ("_win32")
	elseif (os.is("linux")) then
		targetsuffix ("_linux")
	end
	
	configurations { "Release" }
	
	configuration "Release"
		defines { "NDEBUG" }
		flags{ "Optimize", "FloatFast" }
	
	project "gmsv_libnoise"
		defines { "GMMODULE", "_CRT_SECURE_NO_WARNINGS" }
		kind "SharedLib"
		