    -- premake5.lua
workspace "UdanSandbox"

    architecture "x86_64"
    startproject "udan_sandbox"

    configurations
    { 
        "Debug",
        "Release",
        "Dist"
    }

    flags {
        "MultiProcessorCompile"
    }

    -- Log library
    defines { "BUILD_LOGURU", "BUILD_SPDLOG" }
    -- Window library
    defines { "BUILD_GLFW" }

    defines { "USE_SPDLOG" }
    -- defines { "PRINT_LINE" }

    defines { "ENTITY_CAPACITY=1000000" }

    filter "Debug"
        defines { "DEBUG" }

    filter "Release"
        optimize "Full"


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Udan Engine"
    include "Udan/udan_core"
    include "Udan/udan_debug"
    include "Udan/udan_ecs"
    include "Udan/udan_utils"
    include "Udan/udan_window"
    -- Log lib
    --filter "BUILD_LOGURU"
      --  include "Udan/udan_loguru"
    -- filter "BUILD_SPDLOG"
       --include "Udan/udan_spdlog"
    -- Graphic lib
    filter "BUILD_GLFW"
        include "Udan/udan_glfw"

group "Unit Tests"
    include "Tests/core_test"
    include "Tests/utils_test"
    include "Tests/ecs_test"

group ""

project "udan_sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    files {
        "src/**.cpp",
        "include/**.h"
    }

    links { "udan_core", "udan_debug", "udan_ecs", "udan_window", "Winmm", "udan_utils" }

    includedirs {
        "include", 
        "Udan/udan_core/include/",
        "Udan/udan_debug/include/",
        "Udan/udan_ecs/include/",
        "Udan/udan_window/include/",
        "Udan/udan_utils/include/",

        "Udan/ThirdParties/SpdLog/include"
    }

-- group "ThirdParties"
--     include "Udan/ThirdParties/GLFW"
