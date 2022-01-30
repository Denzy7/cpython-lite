set(PYSRCDIR ${CMAKE_SOURCE_DIR}/${python_version})

#the loader used to load static libraries (.dll, .so)
if(WIN32)
	set(lib_loader dynload_win.c)
else()
	set(lib_loader dynload_shlib.c)
endif()

#a path module for path resolution
if(WIN32)
	set(path_module PC/getpathp.c)
else()
	set(path_module Modules/getpath.c)
endif()


#default modules
set(default_modules
		${path_module}
		Modules/main.c
		Modules/gcmodule.c
		
		Modules/_io/_iomodule.c

		Modules/_io/iobase.c
		Modules/_io/fileio.c
		Modules/_io/bufferedio.c
		Modules/_io/textio.c
		Modules/_io/bytesio.c
		Modules/_io/stringio.c
		
		#get build info
		Modules/getbuildinfo.c
		)

#parser
set(parser
		Parser/pegen/pegen.c
		Parser/pegen/parse.c
		Parser/pegen/parse_string.c
		Parser/pegen/peg_api.c
		
		Parser/acceler.c
		Parser/grammar1.c
		Parser/listnode.c
		Parser/node.c
		Parser/parser.c
		Parser/token.c
		)
		
#default python
set(default_python
		Python/_warnings.c
		Python/Python-ast.c
		Python/asdl.c
		Python/ast.c
		Python/ast_opt.c
		Python/ast_unparse.c
		Python/bltinmodule.c
		Python/ceval.c
		Python/codecs.c
		Python/compile.c
		Python/context.c
		Python/dynamic_annotations.c
		Python/errors.c
		#frozenmain.c causes link errors on win32
		#Python/frozenmain.c
		Python/future.c
		Python/getargs.c
		Python/getcompiler.c
		Python/getcopyright.c
		Python/getplatform.c
		Python/getversion.c
		Python/graminit.c
		Python/hamt.c
		Python/hashtable.c
		Python/import.c
		Python/importdl.c
		Python/initconfig.c
		Python/marshal.c
		Python/modsupport.c
		Python/mysnprintf.c
		Python/mystrtoul.c
		Python/pathconfig.c
		Python/peephole.c
		Python/preconfig.c
		Python/pyarena.c
		Python/pyctype.c
		Python/pyfpe.c
		Python/pyhash.c
		Python/pylifecycle.c
		Python/pymath.c
		Python/pystate.c
		Python/pythonrun.c
		Python/pytime.c
		Python/bootstrap_hash.c
		Python/structmember.c
		Python/symtable.c
		Python/sysmodule.c
		Python/thread.c
		Python/traceback.c
		Python/getopt.c
		Python/pystrcmp.c
		Python/pystrtod.c
		Python/pystrhex.c
		Python/dtoa.c
		Python/formatter_unicode.c
		Python/fileutils.c
		
		#lib loader
		Python/${lib_loader}
		
		#freezing modules 
		Python/frozen.c
		)

#python types/objects
set(python_objects
		Objects/abstract.c
		Objects/accu.c
		Objects/boolobject.c
		Objects/bytes_methods.c
		Objects/bytearrayobject.c
		Objects/bytesobject.c
		Objects/call.c
		Objects/capsule.c
		Objects/cellobject.c
		Objects/classobject.c
		Objects/codeobject.c
		Objects/complexobject.c
		Objects/descrobject.c
		Objects/enumobject.c
		Objects/exceptions.c
		Objects/genericaliasobject.c
		Objects/genobject.c
		Objects/fileobject.c
		Objects/floatobject.c
		Objects/frameobject.c
		Objects/funcobject.c
		Objects/interpreteridobject.c
		Objects/iterobject.c
		Objects/listobject.c
		Objects/longobject.c
		Objects/dictobject.c
		Objects/odictobject.c
		Objects/memoryobject.c
		Objects/methodobject.c
		Objects/moduleobject.c
		Objects/namespaceobject.c
		Objects/object.c
		Objects/obmalloc.c
		Objects/picklebufobject.c
		Objects/rangeobject.c
		Objects/setobject.c
		Objects/sliceobject.c
		Objects/structseq.c
		Objects/tupleobject.c
		Objects/typeobject.c
		Objects/unicodeobject.c
		Objects/unicodectype.c
		Objects/weakrefobject.c
		)

#note, python should build without any extra modules and be able to get basic functions like
#Py_GetBuildInfo()
#Py_GetCompiler()
#Py_GetPlatform()
#etc... see https://docs.python.org/3/c-api/init.html

#however we need extra modules to be able to fire up and interpretor (or even call Py_Initialize() and other cool functions!)
#we namely need a 
#signal+faults handler, parser+tokenizer, memory allocator, threading, weakref, io and codecs
#and of course several os modules
#this will depend on your system and will determine how python runs the system

#strangely enough, the os module is Modules/posixmodule.c
#it contains both linux and windows functions. The catch is that it uses config/{os}/pyconfig.h and config/{os}/config.c to find OS functions which needs
#an extensive configuration process. Find a specially tailored pyconfig.h's for several systems in config directory
#these are put here below
	
set(extra_modules
		#signal (interupts etc...)
		Modules/signalmodule.c
		#faulthandler
		Modules/faulthandler.c
		
		#tokenizer and parser to read python code. Include a readline module too
		Parser/parsetok.c
		Parser/tokenizer.c
		Modules/_peg_parser.c
		Parser/myreadline.c
		
		#memalloc (traces memory allocations)
		Modules/_tracemalloc.c
		
		#threads
		Modules/_threadmodule.c
		
		#weakref functionality
		Modules/_weakref.c
		
		#input/output
		Modules/_io/_iomodule.c
		
		#codecs/encodings
		Modules/_codecsmodule.c
		
		#os modules (posix)
		#ensure you have patched before building!	
		Modules/posixmodule.c
		
		#and that's it! Py_Main and Py_Initialize should now work!

		#below are some 3 extra modules you need to get round an
		#import hook if embedding python to an application(really recommended)
		Modules/itertoolsmodule.c	
		Modules/_collectionsmodule.c
		Modules/_sre.c

		#add any more modules to bake into python here...(optional)

		#math module
		Modules/mathmodule.c
		Modules/_math.c
		)
		
#file with modules configuration. Edit this file to add/remove modules to be baked
#this is also a chance to patch on top of Win32 modules to add some important stuff
set(modules_config ${CMAKE_SOURCE_DIR}/${conf_dir}/config.c)
if(WIN32)
	list(APPEND default_modules
	       	Modules/_io/winconsoleio.c
		#frozen_dllmain.c causes linking errors mingw
		#PC/frozen_dllmain.c
		PC/dl_nt.c
		PC/winreg.c
		Modules/_winapi.c
		Modules/atexitmodule.c
		)
endif()	

set(PYSRCS
	#comment this out to remove extra modules from build (use with caution)
	${modules_config}
	)

foreach(PYSRC IN LISTS default_modules parser default_python python_objects extra_modules)
	list(APPEND PYSRCS "${PYSRCDIR}/${PYSRC}")
endforeach()

#add the infamous python library
add_library(${python}
		${PYSRCS}
		)


#now that its impossible to build a static version of python for win32, link some mingw stuff 
#to the shared library
#	AND AGAIN. DON'T BUILD STATIC ON MINGW!
#	IT WILL PROBABLY BREAK!
if(WIN32)
	target_link_libraries(${python} ws2_32 version pathcch)
endif()
