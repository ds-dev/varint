# Varint

## Install

    $ python setup.py build_ext --inplace
    $ python -m unittest test

## Performance tests

Compare c/python implementations of read / write operations:

    $ time python performance_write.py py 4000000 tmp
    real    0m12.246s
    user    0m12.058s
    sys     0m0.078s

    $ time python performance_write.py c  4000000 tmp
    real    0m4.153s
    user    0m4.024s
    sys     0m0.108s

    $ time python performance_read.py py 4000000 tmp
    real    0m8.517s
    user    0m8.377s
    sys     0m0.077s

    $ time python performance_read.py c  4000000 tmp
    real    0m2.198s
    user    0m2.090s
    sys     0m0.093s
