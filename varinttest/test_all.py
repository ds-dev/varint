#!/usr/bin/env python3
import os
from sys import version_info
import varint

# This must be compatible with 2.x and 3.x
# (if just avoid print)
# Also looks like issueing fflush from C did
# solve the seek issue
# the buffering=0 is not anymore critical
 
if __name__ == '__main__':
    test_ns = [42,4353,33,666,99,3443]
    test_file = '/tmp/varint-test.txt'

    # write first
    f = open(test_file,'w+b')
    for n in test_ns:
        varint.varint_write(f,n)
    f.flush()
    f.close()

    # check if written
    f = open(test_file,'r+b')
    for exp in test_ns:
        n = varint.varint_read(f)
        assert(n == exp)
    f.close()

    # remove test file
    os.remove(test_file)
