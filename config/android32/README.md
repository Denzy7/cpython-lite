Build using NDK r21 or later. Older versions have not been tested.
It's important you build with API 24 (Android v7.0). Some functions were added to android libc in 21 and some python modules rely on them.
Configure the tree with
`cmake -S . -B <out-of-tree-build> -DCMAKE_TOOLCHAIN_FILE=<NDK_DIR>/build/cmake/android.toolchain.cmake -DANDROID_PLATFORM=24`
This builds a 32-bit (armeabi-v7a) python executable and library. To build for others like arm64 and x86, pass `-DANDROID_ABI=x86`
See [android abis](https://developer.android.com/ndk/guides/cmake#android_abi)
If embedding to and android app, Android studio automatically detects the target platform with gradle option `abiFilters 'x86', 'armeabi-v7a'`
Use gradle option `minSdkVersion=24` to build for Android 7.0
