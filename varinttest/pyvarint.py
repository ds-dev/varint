# -*- coding: utf-8 -*-
"""Python implementation of varint encoding."""


def varint_write(fileobj, n):
    """
    Encodes integer `n` into variable-length format and
    feeds the unsigned integer `b` values to a file.

    :param fileobj: file-like object
    :param n: int
        number to encode
    """
    while True:
        b = n & 127
        n >>= 7
        if n == 0:
            fileobj.write(chr(b))
            break
        else:
            fileobj.write(chr(b | 128))
            n -= 1


def varint_read(fileobj):
    """
    Reads a sequence of unsigned integer byte values from the file,
    decodes them into an integer in variable-length format
    and returns it as the function result.

    :param fileobj: file-like object
    :returns: int
        decoded integer
    """
    n = 0
    shift = 1
    while True:
        b = ord(fileobj.read(1))
        n += (b & 127) * shift
        if (b & 128) == 0:
            break
        shift <<= 7
        n += shift
    return n
