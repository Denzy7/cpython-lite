/* -*- C -*- ***********************************************
Copyright (c) 2000, BeOpen.com.
Copyright (c) 1995-2000, Corporation for National Research Initiatives.
Copyright (c) 1990-1995, Stichting Mathematisch Centrum.
All rights reserved.

See the file "Misc/COPYRIGHT" for information on usage and
redistribution of this file, and for a DISCLAIMER OF ALL WARRANTIES.
******************************************************************/

/* Module configuration */

/* !!! !!! !!! This file is edited by the makesetup script !!! !!! !!! */

/* This file contains the table of built-in modules.
   See create_builtin() in import.c. */

#include "Python.h"

#ifdef __cplusplus
extern "C" {
#endif

extern PyObject* PyInit__signal(void);
extern PyObject* PyInit_faulthandler(void);
extern PyObject* PyInit__peg_parser(void);
extern PyObject* PyInit__thread(void);
extern PyObject* PyInit__weakref(void);
extern PyObject* PyInit__io(void);
extern PyObject* PyInit__codecs(void);

extern PyObject* PyInit_nt(void);

//Extra mods
extern PyObject* PyInit_itertools(void);
extern PyObject* PyInit__collections(void);
extern PyObject* PyInit__sre(void);
extern PyObject* PyInit_math(void);
extern PyObject* PyInit_winreg(void);
extern PyObject* PyInit__winapi(void);
extern PyObject* PyInit_atexit(void);

/* -- ADDMODULE MARKER 1 -- */

extern PyObject* PyMarshal_Init(void);
extern PyObject* PyInit__imp(void);
extern PyObject* PyInit_gc(void);
extern PyObject* PyInit__ast(void);
extern PyObject* _PyWarnings_Init(void);
extern PyObject* PyInit__string(void);

struct _inittab _PyImport_Inittab[] = {

    {"_signal", PyInit__signal},
    {"faulthandler", PyInit_faulthandler},
    {"_peg_parser", PyInit__peg_parser},
    {"_thread", PyInit__thread},
    {"_weakref", PyInit__weakref},
    {"_io", PyInit__io},
    {"_codecs", PyInit__codecs},
    
    {"nt", PyInit_nt},

    //Extra mods
    {"itertools", PyInit_itertools},
    {"_collections", PyInit__collections},
    {"_sre", PyInit__sre},
    {"math", PyInit_math},
    {"_winapi", PyInit__winapi},
    {"winreg", PyInit_winreg},
    {"atexit", PyInit_atexit},

/* -- ADDMODULE MARKER 2 -- */


    /* This module lives in marshal.c */
    {"marshal", PyMarshal_Init},

    /* This lives in import.c */
    {"_imp", PyInit__imp},

    /* This lives in Python/Python-ast.c */
    {"_ast", PyInit__ast},

    /* These entries are here for sys.builtin_module_names */
    {"builtins", NULL},
    {"sys", NULL},

    /* This lives in gcmodule.c */
    {"gc", PyInit_gc},

    /* This lives in _warnings.c */
    {"_warnings", _PyWarnings_Init},

    /* This lives in Objects/unicodeobject.c */
    {"_string", PyInit__string},

    /* Sentinel */
    {0, 0}
};
#ifdef __cplusplus
}
#endif
