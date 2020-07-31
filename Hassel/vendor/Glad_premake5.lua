project "Glad"
    kind "StaticLib"
    language "C"

    targetdir ("../../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../../bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/include/glad/glad.h",
        "%{prj.name}/include/KHR/khrplatform.h",
        "%{prj.name}/src/glad.c"
    }

    includedirs
    {
        "%{prj.name}/include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"

