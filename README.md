# cpython-lite

A lightweight and easy way to build and embed python to applications
# building

Tested on an Arch Linux system using:
- mingw-w64-gcc 11.2.0-1 (Win32)
  - [mingw-w64-cmake](https://aur.archlinux.org/packages/mingw-w64-cmake) - CMake wrapper for MinGW
  - [mingw-w64-environment](https://aur.archlinux.org/packages/mingw-w64-environment) - Environment wrapper
  - [mingw-w64-pkg-config](https://aur.archlinux.org/packages/mingw-w64-pkg-config) - pkg-config wrapper
- GCC gcc 11.1.0-1 (Linux64)
- Clang 12.0.1 (Android armeabi-v7a)

Download an official tarball from [the Python website](https://www.python.org/downloads/source/) (which is recommended)  
You can also clone this repository recursively (which may take a long time)  
`git clone --recursive https://github.com/Denzy7/cpython-lite`  
If you cloned recursively adjust CMakeLists.txt to point where you cloned python. Otherwise, change the version numbers to the version of the downloaded and extracted tarball

Copy [the CMakeLists.txt](cmake-python/CMakeLists.txt) to the directory with python (symlinks also work if on a Linux system)  
`ln -s <full-path-to-cmakelists.txt> <full-path-to-python-directory>`  

Now configure the source  
`cmake -S . -B <out-of-tree-build-directory>`

If configuring for another system, see the various platform-specific tips in [config](config)  
This checks if valid configuration files are available for the system you want to build for. Check for valid config files in the [configs directory](config/)  

If configuration succeeds, build the source  
`cmake --build <out-of-tree-build-directory>`  
You can also pass extra options to speed up builds ( `-j$(nproc)` )

#bootstrapping

Once a build is complete, you need to bootstrap a standard python library for python to use. It contains the basic python scripts python needs to start up.  
You can find various bootstrapping packages in [the bootstrap directory](bootstrap).  
Use [the win32 package](bootstraping/bootstrap-packaging-win32.tar.xz) for a portable solution. You can also use the basic versions but keep in mind it will not work well with embedding especially if using packages i.e. `import <package>.<embedded_module>`  
You can also use a standard python install to bootstrap. However its much better to use a bootstrap package to keep the disk usage minimal  

#porting

If you want to create a new platform config files, you will need a copy of the existing `pyconfig.h`. If porting a similar platform to those in [config](config), just change the defines such as `SIZEOF_INT` to match the said platform. You can also build [the config tool](config/pyconfig-tool.c) and run it on the target machine to get a list of define to change.  
Its also possible for UNIX platforms to share `config.c` files. Be sure to use the `config.c` file for modules. Win32 needs the `config.c` [here](config/win32) to initialize Windows specific modules.
