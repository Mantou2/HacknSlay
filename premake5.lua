solution "HackNSlay"
	configurations {"Debug", "Release"}
	defines {"GLEW_STATIC", "GLM_FORCE_RADIANS","GLM_SWIZZLE"}
	flags {"FatalWarnings"}
	vectorextensions "SSE2"
	--warnings "Extra" Deactivated because gli doesn't build with it.
	includedirs {"HacknSlay_Project/src/","GlewLib/src","../Libs/glm-0.9.5.4/include","../Libs/gli-0.5.1.0/include","../Libs/InteropAdditions"}

	configuration "vs*"
		includedirs { "Libs/SDL2-2.0.3-vc/include"}
		libdirs {"Libs/SDL2-2.0.3-vc/lib/x64","../Libs/SDL2-2.0.3-vc/lib/x86"}

	configuration {"gmake","windows"}
		includedirs {"Libs/SDL2-2.0.3-mingw/x86_64-w64-mingw32/include/SDL2","../Libs/SDL2-2.0.3-mingw/i686-w64-mingw32/include/SDL2"}
		includedirs {"Libs/SDL2_mixer-2.0.0-mingw/x86_64-w64-mingw32/include/SDL2","../Libs/SDL2_mixer-2.0.0-mingw/i686-w64-mingw32/include/SDL2"}
		libdirs {"Libs/SDL2-2.0.3-mingw/x86_64-w64-mingw32/lib","../Libs/SDL2-2.0.3-mingw/i686-w64-mingw32/lib"}
		libdirs {"Libs/SDL2_mixer-2.0.0-mingw/x86_64-w64-mingw32/lib","../Libs/SDL2_mixer-2.0.0-mingw/i686-w64-mingw32/lib"}

	configuration {"gmake", "not windows"}
		includedirs {"/usr/include/SDL2","/usr/local/include/SDL2"}

	project "GlewLib"
		kind "StaticLib"
		language "C"
		location "GlewLib/build"
		includedirs {"GlewLib/src"}
		files { "GlewLib/src/**.h","GlewLib/src/**.c"}

	project "HnS"
		kind "WindowedApp"
		language "C++"
		includedirs {"HacknSlay_Commons/src/"}
		files {"HacknSlay_Project/src/**.h","HacknSlay_Project/src/**.hpp","HacknSlay_Project/src/**.cpp"}
		location "HacknSlay_Project/build"

		-- TODO Build instructions for VS if needed
		configuration {"gmake","windows"}
			buildoptions "-std=gnu++1y"
			postbuildcommands {
				"copy ..\\..\\Libs\\SDL2-2.0.3-mingw\\x86_64-w64-mingw32\\bin\\SDL2.dll SDL2.dll",
				"copy ..\\..\\Libs\\SDL2_mixer-2.0.0-mingw\\x86_64-w64-mingw32\\bin\\*.dll ."
			}
			linkoptions{"-lmingw32 ../../GlewLib/build/GlewLib.lib -lopengl32 -lSDL2main -lSDL2 -lSDL2_mixer"}
			-- Fix for Premake using a .lib suffix for all links-entries on mingw although mingw doesn't expect those
			links {"GlewLib"}

		configuration {"gmake", "linux"}
			buildoptions "-std=gnu++1y"
			links {"GlewLib","GL","SDL2","SDL2_mixer"}
			libdirs {os.findlib("SDL2")}

		configuration {"gmake", "macosx"}
			buildoptions "-std=c++1y"
			links {"GlewLib","OpenGL.framework","SDL2","SDL2_mixer"}
			libdirs {os.findlib("SDL2")}

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
			optimize "Off"

		configuration "Release"
			defines { "NDEBUG" }
			optimize "Full"

