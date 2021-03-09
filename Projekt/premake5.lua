workspace "Projekt"
architecture "x64"
configurations { "Debug", "Release" }
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "Makao"
  location "Makao"
    kind "WindowedApp"
      language "C++"
       cppdialect "C++17"
 targetdir("build/" .. outputdir .. "/")
    objdir("build/" .. outputdir .. "/data/obj/")
files { "source/**.h", "source/**.cpp" }
includedirs { "vendor/SFML-2.5.1/include" }
libdirs { "vendor/SFML-2.5.1/lib" }

links { "opengl32.lib", "freetype.lib", "winmm.lib", "gdi32.lib", "openal32.lib", "flac.lib", "vorbisenc.lib", "vorbisfile.lib", "vorbis.lib", "ogg.lib", "ws2_32.lib" }

  filter "configurations:Debug"
      runtime "Debug"
    symbols "On"

    links { "sfml-audio-d.lib", "sfml-graphics-d.lib", "sfml-main-d.lib", "sfml-network-d.lib", "sfml-system-d.lib", "sfml-window-d.lib" }

  filter "configurations:Release"
      runtime "Release"
    optimize "On"

    links { "sfml-audio.lib", "sfml-graphics.lib", "sfml-main.lib", "sfml-network.lib", "sfml-system.lib", "sfml-window.lib" }