#include <stdio.h>
#include "Python.h"

#define TRUE 1

#define VARINT_MASK 127
#define VARINT_BASE 128
#define VARINT_SHIFT_MASK 7

#ifdef HAVE_PYTHON3
void __varint_write(PyObject* f, int n){
#else
void __varint_write(FILE* f, int n){
#endif
	int b;
    while (TRUE) {
        b = n & VARINT_MASK;
        n >>= VARINT_SHIFT_MASK;
        if (n == 0) {
#ifdef HAVE_PYTHON3
#else
        	fputc(b,f);
#endif
            break;
        }
        else {
#ifdef HAVE_PYTHON3

#else
        	fputc(b|VARINT_BASE,f);
#endif
            n--;
        }
    }
}

#ifdef HAVE_PYTHON3
int __varint_read(PyObject* f) {
	PyObject* t;
	char* tc;
#else
int __varint_read(FILE* f) {
#endif
    char b = 0;
	int n, shift;
	n = 0;
	shift = 1;
    while (TRUE) {
/* Stupid Python3 I/O workaround! */
#ifdef HAVE_PYTHON3
    	/* Read the damn 1 byte using Python API */
    	t = PyFile_GetLine(f,1);
    	/* Make sure it is byte */
    	if  PyByteArray_Check(t) {
    		printf("PyByteArray_Check OK!\n");
    	} else {
    		printf("PyByteArray_Check NOK!\n");
    		t = PyByteArray_FromObject(t);
    		/* Get the C pointer to char array */
			tc = PyByteArray_AsString(t);
			/* Get the char value */
			b = tc[0];
    	}
#else
        b = fgetc(f);
#endif
        n += (b & VARINT_MASK) * shift;
        if ((b & VARINT_BASE) == 0) {
            break;
        }
        shift <<= VARINT_SHIFT_MASK;
        n += shift;
    }
    return n;
}

int varint_read(PyObject* p) {
	int n;
#ifdef HAVE_PYTHON3
	Py_INCREF(p);
	/* obsolette ------------------------
	int fd = PyObject_AsFileDescriptor(p);
	FILE* f = fdopen(fd, "r+b");
	*/
/*	printf("C Seek pointer at %ld before reading\n", ftell(f));*/
	n = __varint_read(p);
/*	printf("C Seek pointer at %ld after reading\n", ftell(f)); */
	Py_DECREF(p);
#else
	PyFileObject* p2 = (PyFileObject*) p;
	FILE* f = PyFile_AsFile(p);
	PyFile_IncUseCount(p2);
	n = __varint_read(f);
	PyFile_DecUseCount(p2);
#endif

	return n;
}

void varint_write(PyObject* p, int n) {
#ifdef HAVE_PYTHON3
	Py_INCREF(p);
	int fd = PyObject_AsFileDescriptor(p);
	FILE* f = fdopen(fd, "r+b");
/*	printf("C Seek pointer at %ld before writing\n", ftell(f)); */
#else
	PyFileObject* p2 = (PyFileObject*) p;
	FILE* f = PyFile_AsFile(p);
	PyFile_IncUseCount(p2);
#endif
	__varint_write(f,n);
#ifdef HAVE_PYTHON3
	fflush(f);
/*	printf("C Seek pointer at %ld after writing\n", ftell(f)); */
	Py_DECREF(p);
#else
	PyFile_DecUseCount(p2);
#endif
}

