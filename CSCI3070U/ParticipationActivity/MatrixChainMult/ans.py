def matrixChainMultiplication(p):
    n = len(p)
    m, s = [[0 for i in range(n)] for i in range(n)], [[0 for i in range(n)] for i in range(n)]
    
    for i in range(n):
        m[i][i] = 0
    
    for l in range(1, n-1):
        for i in range(1, n-l):
            j = i + l
            minimum = float('inf')
            for k in range(1, j-1):
                 q= m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                 if q < minimum:
                     minimum = q
                     s[i][j] = k
                     
            print(f'i: {i}\tj: {j}')
            m[i][j] = minimum
    return m[1][n-1]


print(matrixChainMultiplication([5, 4, 2, 6, 7]))