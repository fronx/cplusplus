solution "CPlusPlus"
  configurations { "Debug", "Release" }
  buildoptions "-std=c++11 -stdlib=libc++"

  project "Dijkstra"
    kind "ConsoleApp"
    language "C++"
    files { "2_dijkstra.cpp", "2_dijkstra/**.h", "2_dijkstra/**.cpp" }

    configuration "Debug"
      defines { "DEBUG" }

    configuration "Release"
      defines { "NDEBUG" }

  -- A project defines one build target
  project "MyApplication"
    kind "ConsoleApp"
    language "C++"
    files { "**.h", "**.cpp" }
