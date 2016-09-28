from distutils.core import setup, Extension

setup (
    name = 'varint',
    version = '0.1',
    author      = "SWIG Docs",
    description = """Simple swig example from docs""",
    ext_modules = [
        Extension("_varint", sources=["varint.c", "varint.i"])
    ],
    py_modules = ["varint"],
)
