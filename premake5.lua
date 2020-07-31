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

IncludeDir = {}
IncludeDir["GLFW"] = "Hassel/vendor/GLFW/include"
IncludeDir["Glad"] = "Hassel/vendor/Glad/include"

include "Hassel/vendor/GLFW_premake5.lua"
include "Hassel/vendor/Glad_premake5.lua"

project "Hassel"
    location "Hassel"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "hslpch.h"
    pchsource "%{prj.name}/src/hslpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}"
    }

    links
    {
        "GLFW",
        "Glad",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HASSEL_PLATFORM_WINDOWS",
            "HASSEL_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
        
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }   

    filter "configurations:Debug"
        defines "HSL_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "HSL_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        buildoptions "/MD"
        defines "HSL_DIST"
        optimize "On"

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
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "HSL_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "HSL_DIST"
        buildoptions "/MD"
        optimize "On"
