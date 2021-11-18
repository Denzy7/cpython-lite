/* Minimal main program -- everything is loaded from the library */

#include "Python.h"

#define bootstrap_d "bootstrap"

void init_py()
{
	Py_NoSiteFlag = 1;
	Py_FrozenFlag = 1;
	Py_IgnoreEnvironmentFlag = 1;

    printf("loading libs\n");
    printf("mock file\n");
    const char* bootstrap_d2 = bootstrap_d "/ok.txt";
    
    FILE* fff = fopen(bootstrap_d2, "wb");

if(!fff)
{
	printf("Unable to create a mock file in %s. Ensure the directory is writable\n", bootstrap_d2);
	exit(1);
}

    const char* text = "Hello\n\0";
    fwrite(text, 1, sizeof(text), fff);
    fclose(fff);
    printf("mock file done\n");
    
    
    
    wchar_t* home = Py_DecodeLocale(bootstrap_d, NULL);

    Py_SetPath(home);
	
    Py_Initialize();

//Import hook for embedding python and wanting to hardcode packages (optional)
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


#ifdef MS_WINDOWS
int
main(int argc, wchar_t **argv)
{

init_py();
	
    return Py_Main(argc, argv);
}
#else
int
main(int argc, char **argv)
{
init_py();
	
    return Py_BytesMain(argc, argv);
}
#endif
