import unittest
import varint
import os


class TestVarint(unittest.TestCase):

    def setUp(self):
        self.test_file = '/tmp/varint-test.txt'
        f = open(self.test_file, 'w')
        f.close()

    def tearDown(self):
        os.remove(self.test_file)

    def test_size(self):
        f = open(self.test_file, 'r+b')

        # test one byte
        varint.varint_write(f, 2 ** 0)
        self.assertEqual(f.tell(), 1)
        f.seek(0)

        varint.varint_write(f, 2 ** 6)
        self.assertEqual(f.tell(), 1)
        f.seek(0)

        # test two bytes
        varint.varint_write(f, 2 ** 7)
        self.assertEqual(f.tell(), 2)
        f.seek(0)

        varint.varint_write(f, 2 ** 14)
        self.assertEqual(f.tell(), 2)
        f.seek(0)

        # test three byte
        varint.varint_write(f, 2 ** 15)
        self.assertEqual(f.tell(), 3)
        f.seek(0)

        varint.varint_write(f, 2 ** 21)
        self.assertEqual(f.tell(), 3)
        f.seek(0)

        f.flush()
        f.close()


if __name__ == '__main__':
    unittest.main()
