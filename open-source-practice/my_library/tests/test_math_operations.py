from my_library.useful_utils.math_operations import add, subtract, multiply, divide

def test_add():
    assert add(2, 3) == 5
    assert add(-1, 6) == 5
    assert add(99, 1) == 100

def test_subtract():
    assert subtract(2, 3) == -1
    assert subtract(-1, 6) == -7
    assert subtract(99, 1) == 98

def test_multiply():
    assert multiply(2, 3) == 6
    assert multiply(-1, 6) == -6
    assert multiply(99, 1) == 99

def test_divide():
    assert divide(10, 2) == 5
    assert divide(20, 4) == 5
    assert divide(98, -2) == -49