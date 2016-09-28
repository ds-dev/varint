#!/usr/bin/env python27

import varint

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
    f.close()
