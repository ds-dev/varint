#!/usr/bin/env python27

import varint
import os

if __name__ == '__main__':
    f = open('./varint.txt','r+b')
    f.seek(1)
    assert f.read(1) == 'B'
    assert f.read(1) == 'C'
    assert f.tell() == 3
    assert varint.test_file_seek(f, 0) == 'D'
    assert f.tell() == 4
    assert f.read(1) == 'E'
    assert f.tell() == 5
    f.seek(1)
    assert f.read(1) == 'B'
    f.seek(0)
    assert varint.test_file_seek(f, 0) == 'A'
    assert f.tell() == 1
    f.seek(0)
    assert varint.test_file_seek(f, 0) == 'A'
    assert f.tell() == 1
    f.seek(0)
    assert f.read(1) == 'A'
    assert varint.test_file_seek(f,0) == 'B'
    f.seek(1, os.SEEK_CUR)
    assert varint.test_file_seek(f,0) == 'D'
    assert f.read(1) == 'E'
    f.close()
