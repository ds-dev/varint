#include <stdio.h>
#include "Python.h"

#define TRUE 1

#define VARINT_MASK 127
#define VARINT_BASE 128
#define VARINT_SHIFT_MASK 7

void __varint_write(FILE* f, int n){
	int b;
    while (TRUE) {
        b = n & VARINT_MASK;
        n >>= VARINT_SHIFT_MASK;
        if (n == 0) {
            fputc(b,f);
            break;
        }
        else {
            fputc(b|VARINT_BASE,f);
            n--;
        }
    }
}

int __varint_read(FILE* f) {
    char b;
	int n, shift;
	n = 0;
	shift = 1;
    while (TRUE) {
        b = fgetc(f);
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
	int fd = PyObject_AsFileDescriptor(p);
	FILE* f = fdopen(fd, "r+b");
/*	printf("C Seek pointer at %ld before reading\n", ftell(f));*/
#else
	PyFileObject* p2 = (PyFileObject*) p;
	FILE* f = PyFile_AsFile(p);
	PyFile_IncUseCount(p2);
#endif
	n = __varint_read(f);
#ifdef HAVE_PYTHON3
	fflush(f);
/*	printf("C Seek pointer at %ld after reading\n", ftell(f)); */
	Py_DECREF(p);
#else
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

