# Variable-Length Integer Encoding

[Variable-length encoding](https://en.wikipedia.org/wiki/Variable-length_quantity) enables to store
integers using variable amount of bytes so that smaller integers consume less space than the bigger ones.
For example, integers up to 128 fit perfectly into one byte, integers up to 16.512 - into two bytes, and so on.
If we need to store millions of integers (as in the case of storage systems), the gain can be substantial.

This repository contains Python and C implementations of varint-encoding, as well as performance benchmarks.


## Install

    $ python setup.py build_ext --inplace
    $ python -m unittest -v varinttest.test

## Performance tests
We compared *C* and *Python* implementations of *varint-encoding*.
As the results below indicate, c-encoder is about 3 times faster that the python version, and c-decoder is 4 times faster than the python version.

**Endoding**

    $ time python -m varinttest.performance.write py 4000000 tmp
    real    0m12.246s
    user    0m12.058s
    sys     0m0.078s

    $ time python -m varinttest.performance.write c  4000000 tmp
    real    0m4.153s
    user    0m4.024s
    sys     0m0.108s

**Decoding**

    $ time python -m varinttest.performance.read py 4000000 tmp
    real    0m8.517s
    user    0m8.377s
    sys     0m0.077s

    $ time python -m varinttest.performance.read c  4000000 tmp
    real    0m2.198s
    user    0m2.090s
    sys     0m0.093s

## Credits
Special thanks to [Artjom Lind](https://github.com/ds-dev) for providing c-implementation of varint-encoding.
