 %module varint
 %{
 #include <stdio.h>
 #include "Python.h"
 /* Put header files here or function declarations like below */
 extern int varint_read(PyObject* p);
 extern void varint_write(PyObject* p, int n);
 %}

 extern int varint_read(PyObject* p);
 extern void varint_write(PyObject* p, int n);
