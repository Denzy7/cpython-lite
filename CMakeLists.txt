cmake_minimum_required(VERSION 3.10)

project(LibPython VERSION 0.1)

#flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPy_BUILD_CORE")
if(NOT DEFINED pyver)
	message(FATAL_ERROR "define python version -Dpyver=major.minor.build")
endif()
string(REPLACE "." ";" pyver_list ${pyver})

list(GET pyver_list 0 python_version_major)
list(GET pyver_list 1 python_version_minor)
list(GET pyver_list 2 python_version_build)

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

#cmake with python
include(cmake-python/CMakeLists.txt)
link_directories(${CMAKE_BINARY_DIR}/cmake-python)

#Basic Python interprator
add_executable(py-lite main/python.c)

#Basic embedding with C
add_executable(embed main/embed.c)
message("py : ${python}")
#droid and win32 dont need any custom links, unix needs m(if used), pthread, dl and util
if(WIN32 OR ANDROID)
	target_link_libraries(py-lite ${python} )
	target_link_libraries(embed ${python} )
elseif(UNIX)
	target_link_libraries(py-lite ${python} m pthread util dl)
	target_link_libraries(embed ${python} m pthread util dl)
endif()
