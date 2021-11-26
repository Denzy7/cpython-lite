Config files are a combination of a `pyconfig.h` and a `config.c`

`pyconfig.h` contains all necessary options when building python.  
`config.c` contains all modules to be built into the library

As you might expect, building a massive library like python has many configurations. And `pyconfig.h` when unconfigured is about 1800 lines! However only some basic
options are needed to build such as memory sizes and available system calls. I've stripped out the uneeded defines to the most basic for a minimal Python build.

Also there is a patch for posixmodule.c here that enables MinGW support by adding its define is line 298-300 and setting a path separator (yes, its that simple!)

When porting to another platform, pyconfig-tool.c when built when help you get various defines needed for `pyconfig.h`
