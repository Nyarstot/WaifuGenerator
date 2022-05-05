workspace "WaifuGenerator"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "WaifuGenerator"
    location "WaifuGenerator"
    kind "ConsoleApp"
    language "C++"
    toolset "v143"

    targetdir ("bin" .. outputdir .. "/%{prj.name}")
    objdir ("int" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/include/**.cpp"
    }

    filter "system:windows" 
        cppdialect "C++17"
        systemversion "latest"
    
    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"