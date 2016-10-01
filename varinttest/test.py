import unittest
import os
import random

from . import varint as cvarint, pyvarint


class TestVarint(unittest.TestCase):
    def setUp(self):
        self.test_file = 'varint.test.{}.tmp'.format(random.randint(0, 2 ** 31))

    def tearDown(self):
        os.remove(self.test_file)

    def test_size_py(self):
        self.__test_size(pyvarint)

    def test_size_c(self):
        self.__test_size(cvarint)

    def test_rw_c(self):
        self.__test_rw(cvarint)

    def test_rw_py(self):
        self.__test_rw(pyvarint)

    def __test_size(self, varint):
        with open(self.test_file, 'w+b') as f:
            # test one byte
            varint.varint_write(f, 2 ** 0)
            self.assertEqual(f.tell(), 1)
            f.seek(0)

            varint.varint_write(f, 2 ** 7 - 1)
            self.assertEqual(f.tell(), 1)
            f.seek(0)

            # test two bytes
            varint.varint_write(f, 2 ** 7)
            self.assertEqual(f.tell(), 2)
            f.seek(0)

            varint.varint_write(f, 2 ** 14 + 2 ** 7 - 1)
            self.assertEqual(f.tell(), 2)
            f.seek(0)

            # test three bytes
            varint.varint_write(f, 2 ** 14 + 2 ** 7)
            self.assertEqual(f.tell(), 3)
            f.seek(0)

            varint.varint_write(f, 2 ** 21 + 2 ** 14 + 2 ** 7 - 1)
            self.assertEqual(f.tell(), 3)
            f.seek(0)

            # test four bytes
            varint.varint_write(f, 2 ** 21 + 2 ** 14 + 2 ** 7)
            self.assertEqual(f.tell(), 4)
            f.seek(0)

            varint.varint_write(f, 2 ** 28 + 2 ** 21 + 2 ** 14 + 2 ** 7 - 1)
            self.assertEqual(f.tell(), 4)
            f.seek(0)

    def __test_rw(self, varint):
        with open(self.test_file, 'w+b') as f:
            for pw in range(31):
                n = 2 ** pw
                varint.varint_write(f, n)
                f.seek(0)
                self.assertEqual(varint.varint_read(f), n)
                f.seek(0)

            n = 128
            varint.varint_write(f, n)
            f.seek(0)
            self.assertEqual(varint.varint_read(f), n)
            f.seek(0)


if __name__ == '__main__':
    unittest.main()
