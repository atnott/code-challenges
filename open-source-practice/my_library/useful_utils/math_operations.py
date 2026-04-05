def add(a: int, b: int) -> int:
    """Return the sum of two numbers."""
    return a + b

def subtract(a: int, b: int) -> int:
    """Return the difference between two numbers."""
    return a - b

def multiply(a: int, b: int) -> int:
    """Return the product of two numbers."""
    return a * b

def divide(a: int, b: int) -> float:
    """
    Return the result of dividing two numbers.

    If b is zero, raise a ValueError.
    """
    if b == 0:
        raise ValueError("Cannot divide by zero")
    return a / b