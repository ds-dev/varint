#!/usr/bin/env python3
import os
from sys import version_info
import varint
 
if __name__ == '__main__':
    test_ns = [42,4353,33,666,99,3443]
    test_file = '/tmp/varint-test.txt'

    # write first
    f = open(test_file,'w+b',buffering=0)
    for n in test_ns:
        varint.varint_write(f,n)
    f.flush()
    f.close()

    # check if written
    f = open(test_file,'r+b')
    for exp in test_ns:
        n = varint.varint_read(f)
        print ('Varint read: ', n)
        print ('Expected: ', exp)
        assert(n == exp)
    f.close()

    # remove test file
    os.remove(test_file)
