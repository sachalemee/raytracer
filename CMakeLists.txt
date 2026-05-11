cmake_minimum_required(VERSION 3.10)
project(Raytracer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIGPP REQUIRED libconfig++)

if(MSVC) # Pour windows
    add_compile_options(/W4 /WX)
else() # Pour Linux
    add_compile_options(-Wall -Wextra -Werror)
endif()

include_directories(
    include 
    include/Exceptions
    include/Factory
    include/Interfaces
    include/Lights
    include/Materials
    include/Math
    include/Primitives
    include/RayTracer
    include/Templates
    ${LIBCONFIGPP_INCLUDE_DIRS}
)
file(GLOB_RECURSE CORE_SOURCES src/*.cpp)
add_executable(raytracer ${CORE_SOURCES})
target_link_libraries(raytracer PRIVATE ${LIBCONFIGPP_LIBRARIES})
