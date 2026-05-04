cmake_minimum_required(VERSION 3.28)
project(opc_ua_demo)

# Set compiler to use Xcode SDK
if (APPLE)
    execute_process(
            COMMAND xcrun --show-sdk-path
            OUTPUT_VARIABLE SDKROOT
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(CMAKE_OSX_SYSROOT "${SDKROOT}" CACHE PATH "macOS SDK path" FORCE)
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

option(BUILD_TESTING "Build tests" ON)

# Where to find our CMake modules. Needs to be called before any add_subdirectory for them to have access to the variable
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

file(GLOB SOURCES
        src/*.cpp
)

add_library(${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_sources(${PROJECT_NAME}
        PRIVATE ${SOURCES})

# See: https://decovar.dev/blog/2021/03/08/cmake-cpp-library/#include-directories
target_include_directories(${PROJECT_NAME}
        PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_subdirectory(app)

if (BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
else ()
    message(STATUS "Tests will not be compiled")
endif ()


