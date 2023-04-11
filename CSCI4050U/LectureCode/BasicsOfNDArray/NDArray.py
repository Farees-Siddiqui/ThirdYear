import numpy as np

x_array = np.array([
    [190, 170, 130],
    [105, 122, 111]
])

# print(f'The whole array = {x_array}')
print(f'A value         = {x_array[0, 2]}')
print(f'The last value  = {x_array[-1, -1]}')
print(f'A row           = {x_array[0]}')
print(f'A column        = {x_array[:, -1]}')
print(f'A subarray      = (Next Line)\n{x_array[:, 1:]}')

