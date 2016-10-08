#!/bin/bash
rm -rf build
rm varinttest/*.so
python setup.py build_ext --inplace
