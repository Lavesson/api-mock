cmake_minimum_required(VERSION 2.8.8)
add_definitions(-DUNICODE -D_UNICODE -DDLL_EXPORTS)

project(api-mock)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
CHECK_CXX_COMPILER_FLAG("-Wc++11-extensions" COMPILER_SUPPORTS_CXX11_EXTENSIONS)
CHECK_CXX_COMPILER_FLAG("-stdlib=libc++" COMPILER_SUPPORTS_LIBCXX)

if(COMPILER_SUPPORTS_LIBCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	message(STATUS "Supports libc++")
endif()

if(NOT MSVC)
	if(COMPILER_SUPPORTS_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")	
		message(STATUS "Supports -std=c++11")
	elseif(COMPILER_SUPPORTS_CXX0X)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
		message(STATUS "Supports -std=c++0x")
	elseif(COMPILER_SUPPORTS_CXX11_EXTENSIONS)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wc++11-extensions")
		message(STATUS "Supports -Wc++11-extensions")
	else()
        message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
	endif()
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

if (WIN32)
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/arch/unix/server.cpp")
elseif (UNIX)
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/arch/win32/server.cpp")
endif()

add_library(core OBJECT ${HEADER_FILES} ${SOURCE_FILES})
add_executable(api-mock $<TARGET_OBJECTS:core> "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Dependencies
add_subdirectory(www)
add_subdirectory(test)

