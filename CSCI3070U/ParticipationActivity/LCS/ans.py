'''
X: the first string
Y: the second string
m: the length of X
n: the length of Y
'''

def LCSLength(X, Y, m, n):
    c = [[0 for _ in range(n+1)] for _ in range(m+1)]
    # index of last element of outter array is m-1, inner array is n-1
    for i in range(1, m+1):
        c[i][0] = 0
    for j in range(n+1):
        c[0][j] = 0
    
    for i in range(m+1):
        for j in range(n+1):
            if X[i-1] == Y[j-1]:
                c[i][j] = c[i-1][j-1] + 1
            elif c[i-1][j] >= c[i][j-1]:
                c[i][j] = c[i-1][j]     
            else:
                c[i][j] = c[i][j-1]
    return c[m-1][n-1]

print(LCSLength("ABCB", "BDCAB", 4, 5))