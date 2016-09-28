 %module varint
 %{
 #include <stdio.h>
 #include "Python.h"
 /* Put header files here or function declarations like below */
 extern char test_file_seek(PyObject* p, unsigned int seek);
 %}

 extern char test_file_seek(PyObject* p, unsigned int seek);

