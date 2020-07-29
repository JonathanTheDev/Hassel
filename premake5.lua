workspace "Hassel"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Hassel"
    location "Hassel"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HASSEL_PLATFORM_WINDOWS",
            "HASSEL_BUILD_DLL"
        }
        
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }   

    filter "configurations:Debug"
        defines "HSL_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HSL_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "HSL_DIST"
        symbols "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Hassel/vendor/spdlog/include",
        "Hassel/src"
    }

    links
    {
        "Hassel"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HASSEL_PLATFORM_WINDOWS"
        }
        
    filter "configurations:Debug"
        defines "HSL_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HSL_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "HSL_DIST"
        symbols "On"
