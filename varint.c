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
	PyFileObject* p2 = (PyFileObject*) p;
	FILE* f = PyFile_AsFile(p);
	PyFile_IncUseCount(p2);
	n = __varint_read(f);
	PyFile_DecUseCount(p2);
	return n;
}

void varint_write(PyObject* p, int n) {
	PyFileObject* p2 = (PyFileObject*) p;
	FILE* f = PyFile_AsFile(p);
	PyFile_IncUseCount(p2);
	__varint_write(f,n);
	PyFile_DecUseCount(p2);
}

int main() {

	return 0;
}
