"""x is the binary number, n is the length of the binary number, c is the number of bits to be printed per chunk"""
get_bin = lambda x, n, c: ' '.join(format(x, 'b').zfill(n)[i:i+c] for i in range(0, n, c))

def arithmeticShiftRight(x, n) -> str:
    """
    Performs an arithmetic shift right on the binary representation of x by n bits. Prints the result in c-bit chunks.
    x is the number to be shifted
    n is the number of times to shift
    """
    for i in range(int(n)):
        x = x >> 1
    return get_bin(x, 11, 5)

def arithmeticShiftLeft(x, n) -> str:
    """
    Performs an arithmetic shift left on the binary representation of x by n bits. Prints the result in c-bit chunks.
    x is the number to be shifted
    n is the number of times to shift
    """
    for i in range(int(n)):
        x = x << 1
    return get_bin(x, 11, 5)

def decimalToHex(x) -> str:
    """
    Returns the hexadecimal representation of x.
    x is the number to be converted
    """
    return hex(x)

def binaryToDecimal(x) -> int:
    """
    Returns the decimal representation of x.
    x is the binary number to be converted
    """
    return int(x)

# implement a function that takes in a negative decimal number and returns the two's complement representation of that number in n bits
def decimalToBinary(x, n, c) -> str:
    """
    Returns the two's complement representation of x in n bits.
    x is the number to be converted
    n is the number of bits to be used
    c is the number of bits to be printed per chunk
    """
    if x < 0:
        x = 2**n + x
    return get_bin(x, n, c)

print(decimalToBinary(10, 5, 5))