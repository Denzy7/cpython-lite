Build with mingw-w64. MSVC hasn't been tested but that's what upstream python uses for PC builds.  

It very important you build shared not static. This avoid some very annoying link errors when linking the executable.  
Pass `-DBUILD_SHARED_LIBS:BOOL=ON` when configuring the source if your cmake toolchain does not provide this option by default  

If on Arch Linux there are some very nice tools in the AUR just for this.  
- [mingw-w64-cmake](https://aur.archlinux.org/packages/mingw-w64-cmake) - CMake wrapper for MinGW
- [mingw-w64-environment](https://aur.archlinux.org/packages/mingw-w64-environment) - Environment wrapper
- [mingw-w64-pkg-config](https://aur.archlinux.org/packages/mingw-w64-pkg-config) - pkg-config wrapper
Just ensure you use regular `cmake --build <out-of-tree-dir>` when building.
