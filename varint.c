#include <stdio.h>
#include "Python.h"

#define TRUE 1

#define VARINT_MASK 127
#define VARINT_BASE 128
#define VARINT_SHIFT_MASK 7

char test_file_seek(PyObject* p, unsigned int seek) {
	PyFileObject* p2 = (PyFileObject*) p;
	char c;
	FILE* f = PyFile_AsFile(p);
	PyFile_IncUseCount(p2);
	c = fgetc(f);
	PyFile_DecUseCount(p2);
	return c;
}

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

int main() {
	return 0;
}
