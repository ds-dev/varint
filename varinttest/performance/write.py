"""

Usage: python -m varinttest.performance.write (py|c) <SAMPLE_SIZE> <FILE>

"""
import sys

from ..varint import varint_write as encode_c
from ..pyvarint import varint_write as encode_py

if __name__ == "__main__":
    if sys.argv[1] == 'py':
        func = lambda f, n: encode_py(f, n)
    elif sys.argv[1] == 'c':
        func = lambda f, n: encode_c(f, n)
    else:
        raise ValueError('Invalid first argument: "%s". Must be either "c" or "py"' % sys.argv[1])

    n_elements = int(sys.argv[2])
    out_file = sys.argv[3]

    with open(out_file, 'w+b') as f:
        for i in xrange(n_elements):
            n = 2 ** (7 * (i % 5))
            func(f, n)
