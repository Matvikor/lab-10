import ctypes
import os
import unittest

LIB_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "build", "libstack.so"))
lib = ctypes.CDLL(LIB_PATH)

lib.stack_create.argtypes = [ctypes.c_size_t]
lib.stack_create.restype = ctypes.c_void_p

lib.stack_destroy.argtypes = [ctypes.c_void_p]
lib.stack_destroy.restype = None

lib.stack_push.argtypes = [ctypes.c_void_p, ctypes.c_int]
lib.stack_push.restype = ctypes.c_int

lib.stack_pop.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
lib.stack_pop.restype = ctypes.c_int

lib.stack_peek.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
lib.stack_peek.restype = ctypes.c_int

lib.stack_is_empty.argtypes = [ctypes.c_void_p]
lib.stack_is_empty.restype = ctypes.c_int

lib.stack_is_full.argtypes = [ctypes.c_void_p]
lib.stack_is_full.restype = ctypes.c_int

lib.stack_size.argtypes = [ctypes.c_void_p]
lib.stack_size.restype = ctypes.c_size_t

class TestStackPython(unittest.TestCase):
    def setUp(self):
        self.stack = lib.stack_create(2)
        self.assertIsNotNone(self.stack)

    def tearDown(self):
        if self.stack:
            lib.stack_destroy(self.stack)

    def test_basic_flow(self):
        val = ctypes.c_int()
        self.assertEqual(lib.stack_push(self.stack, 42), 0)
        self.assertEqual(lib.stack_push(self.stack, 99), 0)
        self.assertEqual(lib.stack_is_full(self.stack), 1)
        
        self.assertEqual(lib.stack_peek(self.stack, ctypes.byref(val)), 0)
        self.assertEqual(val.value, 99)
        
        self.assertEqual(lib.stack_pop(self.stack, ctypes.byref(val)), 0)
        self.assertEqual(val.value, 99)
        self.assertEqual(lib.stack_pop(self.stack, ctypes.byref(val)), 0)
        self.assertEqual(val.value, 42)
        
        self.assertEqual(lib.stack_is_empty(self.stack), 1)
        self.assertEqual(lib.stack_pop(self.stack, ctypes.byref(val)), 2)

    def test_auto_expand_python(self):
        val = ctypes.c_int()
        for i in range(50):
            self.assertEqual(lib.stack_push(self.stack, i * 10), 0)
        self.assertEqual(lib.stack_size(self.stack), 50)
        for i in range(49, -1, -1):
            self.assertEqual(lib.stack_pop(self.stack, ctypes.byref(val)), 0)
            self.assertEqual(val.value, i * 10)

    def test_error_handling(self):
        self.assertEqual(lib.stack_push(None, 10), 1)

if __name__ == "__main__":
    unittest.main(verbosity=2)