# -*- coding: utf-8 -*-
from struct import pack as struct_pack, unpack as struct_unpack
import io


def varint_encode(n, put):
    """encodes integer n into variable-length format and
    feeds the unsigned integer b values to Put."""
    while True:
        b = n & 127
        n >>= 7
        if n == 0:
            put(chr(b))
            break
        else:
            put(chr(b | 128))
            n -= 1


def varint_decode(get):
    """reads a sequence of unsigned integer byte values by calling
    Get, decodes them into an integer in variable-length format
    and returns it as the function result."""
    n = 0
    shift = 1
    while True:
        b = ord(get(1))
        n += (b & 127) * shift
        if (b & 128) == 0:
            break
        shift <<= 7
        n += shift
    return n
