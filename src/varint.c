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
/**************
 * Passing opened file from Python3
 *
 * NB! This will only work if the file is opened with no buffering
 * in Python3:
 *  	f = open('<filepath>,'r+b',buffering=0)
 *
 * The default however is buffered:
 * 		f = open('<filepath>,'r+b)
 *
 * What happens when we read x bytes the seek pointer is indeed
 * at x position ( f.tell() )
 * This seek pointer position however has nothing to do
 * with the file: it seeks over the buffered data.
 * The real seek pointer of the file might be in fact far away, or even
 * at the end of the file  (Python3 'buffered' it and therefore
 * moved the real seek pointer further away).
 *
 * The IO API of Python3 suggests we may get rid of High-Level I/O
 * encapsulation by setting 'buffering=0' each time we open the file.
 * https://docs.python.org/3.4/library/io.html#raw-i-o
 *
 * Hardly it removes the high-level encapsulation completely, but
 * the 'out-of-sync' seek pointers issue looks gone.
 * (at least for forward-writing).
 *
 * NB! forward-reading is unreliable
 *
 * Despite the disabled 'buffering', once we read from file in C
 * the seek pointers get out of sync. The seek pointer in Python3
 * falls to the end of the file.
 *
 * This was not the case with forward-writing the file:
 * 	 Each time we write: the data gets appended and the file grows;
 * 	 both seek pointers are anyway at the end.
 *
 * Currently we solve the issue by calling fflush after each
 * read/write call from C.
 *
 */
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

