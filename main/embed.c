#include <Python.h>

#define bootstrap_d "bootstrap"

//Basic embedding
static PyObject* module_hello(PyObject* self, PyObject* args)
{
    printf("Hello World! from Python!\n");
    return PyLong_FromLong(0);
};
static PyMethodDef HelloEmbedMethods[] =
{
    { "hello", module_hello, METH_VARARGS, "Hello World! Embed!." },
    { NULL, NULL, 0, NULL}
};

static struct PyModuleDef hello_module =
{
    PyModuleDef_HEAD_INIT,
    "embed",
    "Hello Embedded module",
    -1,
    HelloEmbedMethods
};

PyMODINIT_FUNC PyInit_hello_module()
{
    //Add __path__ for importlib
    //Add it to the main package
    PyObject* mod = PyModule_Create(&hello_module);
    PyModule_AddObject(mod, "__path__", Py_BuildValue("()"));
	
    return mod;
}


//Embedding hand written package
static PyObject* module_test1(PyObject* self, PyObject* args)
{
    printf("Hello World! from Python package!\n");
    return PyLong_FromLong(0);
};

static PyObject* module_test2(PyObject* self, PyObject* args)
{
    printf("%d + %d is %d, -1 that's %d ; quick maths!\n", 2, 2, (2+2), (2+2)-1);
    return PyLong_FromLong(0);
};

static PyMethodDef PackageEmbedMethods[] =
{
    { "test1", module_test1, METH_VARARGS, "Method test1.\n" },
    { "test2", module_test2, METH_VARARGS, "Method test2.\n" },
    { NULL, NULL, 0, NULL}
};

static struct PyModuleDef packaged_module =
{
    PyModuleDef_HEAD_INIT,
    "embed.packaging",
    "Packaged module module",
    -1,
    PackageEmbedMethods
};

PyMODINIT_FUNC PyInit_packaged_module()
{
    return PyModule_Create(&packaged_module );
}

void init_py()
{
   //python flags to prevent loading some unneeded stuff
    Py_NoSiteFlag = 1;
    Py_FrozenFlag = 1;
    Py_IgnoreEnvironmentFlag = 1;

    printf("loading libs\n");
	//try to create a test file to see if directory is writable
    printf("mock file\n");
    const char* bootstrap_d2 = bootstrap_d "/ok.txt";
    
    FILE* fff = fopen(bootstrap_d2, "wb");

    if(!fff)
    {
	printf("unable to create a mock file in %s. ensure the directory is writable\n", bootstrap_d2);
	exit(1);
    }

    const char* text = "hello\n\0";
    fwrite(text, 1, sizeof(text), fff);
    fclose(fff);
    printf("mock file done\n");
    
    
    //decode locale
    wchar_t* home = Py_DecodeLocale(bootstrap_d, NULL);
	//set path to bootstrap
    Py_SetPath(home);
	//start interprator
    Py_Initialize();

   //import hook for embedding python and wanting to hardcode packages (optional)
   //will fail (but not crash python) if no importlib was baked into cpython lib
    PyRun_SimpleString(
        "import importlib.abc\n" \
        "import importlib.machinery\n" \
        "import sys\n" \
        "\n" \
        "\n" \
        "class Finder(importlib.abc.MetaPathFinder):\n" \
        "    def find_spec(self, fullname, path, target=None):\n" \
        "        if fullname in sys.builtin_module_names:\n" \
        "            return importlib.machinery.ModuleSpec(\n" \
        "                fullname,\n" \
        "                importlib.machinery.BuiltinImporter,\n" \
        "            )\n" \
        "\n" \
        "\n" \
        "sys.meta_path.append(Finder())\n" \
    );
}

#define EMBED_BASIC "embed-basic.py"
#define EMBED_PACKAGE "embed-package.py"
int main()
{
    //Append before init
    PyImport_AppendInittab("embed", PyInit_hello_module);
    PyImport_AppendInittab("embed.packaging", PyInit_packaged_module);

    init_py();

    //Basic
    FILE* f_basic = fopen(EMBED_BASIC, "r");
    PyRun_SimpleFile(f_basic,EMBED_BASIC);

    //Package
    FILE* f_pkg = fopen(EMBED_PACKAGE, "r");
    PyRun_SimpleFile(f_pkg,EMBED_PACKAGE);

    return 0;
}
