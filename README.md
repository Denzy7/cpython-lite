# cpython-lite

A lightweight and easy way to build and embed python to applications
# building

Tested on an Arch Linux system using:
- mingw-w64-gcc 11.2.0-1 (Win32)
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
