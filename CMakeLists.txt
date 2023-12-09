cmake_minimum_required(VERSION 3.22)
project("SharedLibrary" VERSION "1.0.0" LANGUAGES C CXX)
set(TARGET "${PROJECT_NAME}_${CMAKE_SYSTEM_NAME}_${TARGET_ARCH}")
set(CMAKE_CXX_STANDARD 17)

list(APPEND SOURCES
	"SharedLibrary.cpp")

add_library(${TARGET} STATIC ${SOURCES})

target_compile_definitions(${TARGET} PRIVATE UNICODE)

if (UNIX)
	target_compile_definitions(${TARGET} PRIVATE __linux__)
	if (${TARGET_ARCH} STREQUAL "x86")
		set(CMAKE_C_FLAGS "-m32 ${CMAKE_C_FLAGS}")
		set(CMAKE_CXX_FLAGS "-m32 ${CMAKE_CXX_FLAGS}")
	endif()
elseif(WIN32)
	set(CMAKE_GENERATOR_TOOLSET "v141_xp")
	target_compile_definitions(${TARGET} PRIVATE _WIN32)
endif()

set(outdir "${CMAKE_INSTALL_PREFIX}/${CMAKE_BUILD_TYPE}")
make_directory(${outdir})
install(TARGETS ${TARGET} DESTINATION ${outdir})