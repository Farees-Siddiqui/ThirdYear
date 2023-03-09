def get_digit(i, num)->int:
    return int((num / 10 ** i) % 10)

print(get_digit(0, 1))