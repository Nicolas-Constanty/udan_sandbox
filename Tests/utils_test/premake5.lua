-- premake5.lua
project "utils_test"
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

    links { "udan_core" , "udan_debug", "Winmm", "udan_utils" }

    includedirs {
        "../../Udan/udan_core/include",
        "../../Udan/udan_debug/include",
        "../../Udan/udan_utils/include",
        "../../Udan/ThirdParties/SpdLog/include"
    }
    