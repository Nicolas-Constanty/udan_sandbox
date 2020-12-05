-- premake5.lua
project "core_test"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    pchheader "pch.h"
    pchsource "pch.cpp"

    files {
        "**.cpp",
        "**.h"
    }

    links { "udan_core" , "udan_debug", "Winmm" }

    includedirs {
        "../../Udan/udan_core/include",
        "../../Udan/udan_debug/include",
        "../../Udan/ThirdParties/SpdLog/include"
    }
    