#!/bin/bash
rm -rf build
rm varinttest/*.so
CFLAGS='-DHAVE_PYTHON3' python3 setup.py build_ext --inplace
