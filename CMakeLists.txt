cmake_minimum_required(VERSION 2.8)
message(STATUS "cmake: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

project(Renderer)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/publish)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/publish)
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
endif()
set(CMAKE_BUILD_TYPE "Release")

FILE(GLOB_RECURSE PIXEL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(Renderer ${PIXEL_FILES})

target_include_directories(Renderer SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb_image)
if(APPLE)
    target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/sdl2_macos/2.0.12_1/include)
endif()
if(MINGW)
    target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/sdl2_mingw32/include)
endif()

if(APPLE)
    target_link_libraries(Renderer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/deps/sdl2_macos/2.0.12_1/lib/libSDL2.a 
PRIVATE "-lm -liconv -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal")
endif()
if (MINGW)
    target_link_libraries(Renderer PRIVATE mingw32 ${CMAKE_CURRENT_SOURCE_DIR}/deps/sdl2_mingw32/lib/libSDL2main.a ${CMAKE_CURRENT_SOURCE_DIR}/deps/sdl2_mingw32/lib/libSDL2.a PRIVATE "-lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -static-libgcc")
endif()