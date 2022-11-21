import random
import time
'''
Farees Siddiqui - 100780513

function execution time for array of size n = 1000  : 0.0029985904693603516
function execution time for array of size n = 10000 : 0.036998748779296875
function execution time for array of size n = 100000: 0.45200204849243164
'''

def mergeSort(A):
    if len(A) > 1:

        mid = len(A)//2 # <- midpoint
        L = A[:mid]
        R = A[mid:]

        mergeSort(L)
        mergeSort(R)

        i = j = k = 0

        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                A[k] = L[i]
                i += 1
            else:
                A[k] = R[j]
                j += 1
            k += 1

        while i < len(L):
            A[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            A[k] = R[j]
            j += 1
            k += 1

# x = [random.randint(0,9) for x in range(1000)]
# start = time.time()
# mergeSort(x)
# print(f'function execution time for array of size n = 1000: {time.time()-start}')

# x = [random.randint(0,9) for x in range(10000)] 
# start = time.time()
# mergeSort(x)
# print(f'function execution time for array of size n = 10000: {time.time()-start}')

# x = [random.randint(0,9) for x in range(100000)]
# start = time.time()
# mergeSort(x)
# print(f'function execution time for array of size n = 100000: {time.time()-start}')



# def F(A, s, e):
#     if s == e:
#         return A[s]
#     mid = A[(s + e)//2]
#     if s < e:
#         return F(A, s, mid) + F(A, mid+1, e)
#     else:
#         return 0

# [1, 2, 3, 4, 5]

'''

'''

# A = [random.randint(0,9) for i in range(10)]
# print(A)
# print(F(A, 0, len(A)))
# print(A)