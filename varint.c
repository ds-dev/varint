#include <stdio.h>
#include "Python.h"

char test_file_seek(PyObject* p, unsigned int seek) {
	PyFileObject* p2 = (PyFileObject*) p;
	FILE* f = PyFile_AsFile(p2);
	PyFile_IncUseCount(p2);
	char c = fgetc(f);
	PyFile_DecUseCount(p2);
	return c;
}

