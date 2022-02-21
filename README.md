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

Tested on Windows 7 using MinGW from [WinLibs](https://winlibs.com). (*The [official installer](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/) is incredibly old and doesn't have libraries to build modern Python*)

Download an official tarball from [the Python website](https://www.python.org/downloads/source/) (which is recommended)  
[Version 3.9.*'s](https://www.python.org/ftp/python/) have been thoroughly tested and are the recommended tarball.

You can also clone this repository recursively (which may take a long time)  
`git clone --recursive https://github.com/Denzy7/cpython-lite`  
If you cloned recursively adjust CMakeLists.txt to point where you cloned python. Otherwise, change the version numbers to the version of the downloaded and extracted tarball.

Now configure the source  
**If configuring for another system other than x86_x64 Linux (linux64), see the various platform-specific tips in** [configs directory](config) 

`cmake -S . -B <out-of-tree-build-directory> -Dpyver=<python-version-using>`  
e.g.  
`cmake -S . -B <out-of-tree-build-directory> -Dpyver=3.9.4`  

This checks if valid configuration files are available for the system you want to build for. Check for valid config files in the [configs directory](config/)  

Patch posixmodule.c if you will be compiling on MinGW (Linux):
`patch -u Python-<pyver>/Modules/posixmodule.c -i config/posixmodule-<pyver>.patch`

If on Windows, adjust `Modules/posixmodule.c` to include the few lines in `config/posixmodule-<pyver>.patch`

Windows users need to also specify `-G "MinGW Makefiles"`. Please note the location where you extracted MinGW and add `<LOCATION>/bin` to your path as environment variable. `<LOCATION>/bin` should contain `mingw32-make.exe`  

If configuration succeeds, build the source  
`cmake --build <out-of-tree-build-directory>`  
You can also pass extra options to speed up builds ( `-j$(nproc)` )

# bootstrapping

Once a build is complete, you need to bootstrap a standard python library for python to use. It contains the basic python scripts python needs to start up.  
You can find various bootstrapping packages in [the bootstrap directory](bootstraping).  

Use [the win32 package](bootstraping/bootstrap-packaging-win32.tar.xz) for a portable solution. You can also use the basic versions but keep in mind it will not work well with embedding especially if using packages i.e. `import <package>.<embedded_module>`  
You can also use a standard python install to bootstrap. However its much better to use a bootstrap package to keep the disk usage minimal  

The main executable looks for a bootstrap directory next to it so ensure you extract a bootstrap package there or copy a Python library there.

# porting

If you want to create a new platform config files, you will need a copy of the existing `pyconfig.h`. If porting a similar platform to those in [configs directory](config), just change the defines such as `SIZEOF_INT` to match the said platform. You can also build [the config tool](config/pyconfig-tool.c) and run it on the target machine to get a list of defines to change.  
Its also possible for UNIX platforms to share `config.c` files. Be sure to use the `config.c` file for modules. Win32 needs the `config.c` [here](config/win32) to initialize Windows specific modules.  

The [library CMakeLists.txt](cmake-python/CMakeLists.txt) can offer some insights and tips for porting.

# known issues

- Causes **SIGSEGV** on Linux if you compile an extension and import it with `py-lite` (*extension will work with your distro's python installation however*)
