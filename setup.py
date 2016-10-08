from setuptools import setup, find_packages, Extension
from os import environ
from sys import version_info

if version_info.major == 3:
    if 'CFLAGS' in environ:
        environ['CFLAGS'] += ' -DHAVE_PYTHON3'
    else:
        environ['CFLAGS'] = '-DHAVE_PYTHON3'

setup(
    name='varinttest',
    version='0.1',
    author="Alexander Tkatsenko",
    description="""Varint test""",
    packages=find_packages(),
    ext_modules=[
        Extension("varinttest._varint",
                  sources=["src/varint.c", "varinttest/varint.i"])
    ],
)
