import numpy as np
from time import time

x = np.arange(5)

print(f'x = {x}')

x[0] = 99

x[3:6] = 99

bigmatrix = np.random.random((1000, 2000))

print(f'bigmatrix size = {bigmatrix.size}')

#
# a loop based computation of sum of max of rows
#

def sum_of_max_loop(bigmatrix):
    m,n = bigmatrix.shape

    max_values = np.full(m, np.nan)

    for row in range(m):
        for col in range(n):
            v = bigmatrix[row, col]
            if col == 0:
                max_values[row] = v
            else:
                max_values[row] = max(max_values[row], v)

    sum_of_max = 0
    for row in range(m):
        sum_of_max += max_values[row]
        
    return sum_of_max

start = time()
sum_of_max = sum_of_max_loop(bigmatrix)
duration_loop = time() - start
    
print("sum_of_max =", sum_of_max)
print("Took: %.4f seconds." % duration_loop)
print('\n-------------------------------------------\n')

# Vectorized computation of sum of max of rows
def sum_of_max_vec(bigmatrix):
    max_values = np.max(bigmatrix, axis=1)
    return np.sum(max_values)

start = time()
sum_of_max = sum_of_max_vec(bigmatrix)
duration_vec = time() - start
    
print("sum_of_max =", sum_of_max)
print("Took: %.4f seconds." % duration_vec)
print("Speed-up factor: %f" % (duration_loop / duration_vec))