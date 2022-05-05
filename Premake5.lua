require('premake5-cuda')

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

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/include/**.cpp"
    }

    -- Add necessary build customization using standard Premake5
    -- This assumes you have installed Visual Studio integration for CUDA
    -- Here we have it set to 11.4
    buildcustomizations "BuildCustomizations/CUDA 11.6"
    cudaPath "/usr/local/cuda" -- Only affects linux, because the windows builds get CUDA from the VS extension

    -- CUDA specific properties
    cudaFiles {"example/*.cu"} -- files NVCC compiles
    cudaMaxRegCount "32"

    -- Compile for all supported architectures (and also in parallel with -t0)
    cudaCompilerOptions {"-arch=sm_52", "-gencode=arch=compute_52,code=sm_52", "-gencode=arch=compute_60,code=sm_60",
                        "-gencode=arch=compute_61,code=sm_61", "-gencode=arch=compute_70,code=sm_70",
                        "-gencode=arch=compute_75,code=sm_75", "-gencode=arch=compute_80,code=sm_80",
                        "-gencode=arch=compute_86,code=sm_86", "-gencode=arch=compute_86,code=compute_86", "-t0"}                      

    -- On Windows, the link to cudart is done by the CUDA extension, but on Linux, this must be done manually
    if os.target() == "linux" then 
        linkoptions {"-L/usr/local/cuda/lib64 -lcudart"}
    end

    filter "system:windows" 
        cppdialect "C++17"
        systemversion "latest"
    
    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        cudaFastMath "On" -- enable fast math for release
        optimize "On"