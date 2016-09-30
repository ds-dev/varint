"""

Usage: performance_read.py (py|c) <SAMPLE_SIZE> <DATA FILE>

"""
from varint import varint_read as decode_c
from pyvarint import varint_decode as decode_py
import sys

if __name__ == "__main__":
    if sys.argv[1] == 'py':
        func = lambda f: decode_py(f.read)
    elif sys.argv[1] == 'c':
        func = lambda f: decode_c(f)
    else:
        raise ValueError('Invalid first argument: "%s". Must be either "c" or "py"' % sys.argv[1])

    n_elements = int(sys.argv[2])
    data_file = sys.argv[3]

    with open(data_file, 'r+b') as f:
        for i in xrange(n_elements):
            func(f)
