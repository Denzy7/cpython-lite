cmake_minimum_required(VERSION 3.10)

project(LibPython VERSION 0.1)

#flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPy_BUILD_CORE")

#punch in number in the order of Python-x.x.x from extracted tarball (tar.gz for windows folk)
set(python_version_major 3)
set(python_version_minor 9)
set(python_version_build 4)

#set to where an extracted tar of python is
set(python_version Python-${python_version_major}.${python_version_minor}.${python_version_build})

#lib
#append m to avoid conflics with a non-build python library
set(python python${python_version_major}.${python_version_minor}m)

#find if 64/32 bit
#set where to find pyconfig.h
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # 64 bits
    if(UNIX)
	    set(conf_dir config/linux64)
    endif()

elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # 32 bits
    if(WIN32)
	    set(conf_dir config/win32)
    elseif(ANDROID)
	    set(conf_dir config/android32)
    endif()
endif()

if(NOT DEFINED conf_dir)
	message(FATAL_ERROR "This system has not compatible pyconfig.h. Please consider porting one...")
endif()

message(STATUS "Using conf_dir ${conf_dir}")

#inclues
include_directories(
${CMAKE_SOURCE_DIR}/${python_version}/Include
${CMAKE_SOURCE_DIR}/${python_version}/Include/internal
${CMAKE_SOURCE_DIR}/${python_version}/Python
${CMAKE_SOURCE_DIR}/${python_version}/Modules
${conf_dir}
)
#Directory to find pyconfig.h
add_subdirectory(${python_version})

add_executable(py-lite main/python.c)

#droid and win32 dont need any custom links, unix needs m(if used), pthread, dl and util
if(WIN32 OR ANDROID)
	target_link_libraries(py-lite ${python} )
elseif(UNIX)
	target_link_libraries(py-lite ${python} m pthread util dl)
endif()
