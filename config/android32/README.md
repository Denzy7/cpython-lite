Build using NDK r21 or later. Older versions have not been tested.  
It's important you build with API 24 (Android v7.0). Some functions were added to android libc in 24 and some python modules rely on them.  
Configure the tree with:  
`cmake -S . -B <out-of-tree-directory> -DCMAKE_TOOLCHAIN_FILE=<NDK_DIR>/build/cmake/android.toolchain.cmake -DANDROID_PLATFORM=24`  

This builds a 32-bit (armeabi-v7a) python executable and library. To build for others like arm64 and x86, append `-DANDROID_ABI=x86`  
See [android abis](https://developer.android.com/ndk/guides/cmake#android_abi)

If embedding to and android app, Android studio automatically detects the target platform with gradle option `abiFilters 'x86', 'armeabi-v7a'`  
Use gradle option `minSdkVersion 24` to build for Android 7.0


# running

To run `py-lite` (main executable) use a terminal emulator like [Termux](https://play.google.com/store/apps/details?id=com.termux)  
To dodge Android file permissions (if phone is not rooted), consider getting the build executable with tools like `wget` in Termux.  
If not installed use:  
`pkg install wget`  

**Its common for Termux mirrors to change (or break), consider getting the** [latest mirrors](https://github.com/termux/termux-packages/wiki/Mirrors). Use primary hosts main mirror

Please checkout [releases](../../releases) and use the url's to the release in `wget` e.g.  
`wget https://github.com/Denzy7/cpython-lite/releases/download/v3.9.4-py-lite/py-lite-3.9.4-android_armeabi_v7a.tar.xz`  
`tar -xvf py-lite-3.9.4-android_armeabi_v7a.tar.xz`


Now extract a [bootstrap package](../../bootstraping) next to the executable:  
`tar -xvf <package>.tar.xz`

Run with:  
`./py-lite`

