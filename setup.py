from setuptools import setup, find_packages, Extension

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
