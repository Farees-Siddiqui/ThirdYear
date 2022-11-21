'''
Farees Siddiqui - 100780513
Nicholas Kissoon - 100742790

The algorithm has 3 parts explodeString(), mergeSort(), and binarySearch()

Time complexities: 
explodeString(): O(n)
mergeSort():     O(nlogn)
binarySearch():  O(logn)
'''
# O(nlogn)
def mergeSort(A):
    if len(A) > 1:

        mid = len(A)//2 
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

# O(logn)
def binarySearch(A, target, low, high):
    if low > high:
        return False
    mid = (low + high) // 2

    if A[mid] == target:
        return True
    elif A[mid] < target:
        return binarySearch(A, target, mid+1, high)
    else:
        return binarySearch(A, target, low, mid-1)

# O(n)
def explodeString(S, index, target,res):
    if index == len(S):
        index = 0
        return res
    sub = S[index:index+len(target)]
    res.append(sub)
    return explodeString(S, index+1, target, res)

string = "You have a long string containing many characters (such as this paragraph), and you want to search for a substring within this string"
targets = ["characters", "want to", "bstring wi", "language"]


explodedStrings = [explodeString(string, 0, targets[i], []) for i in range(len(targets))]

for i in explodedStrings:
    mergeSort(i)

print(f'Targets: {len(targets)}, Length of explodedStrings: {len(explodedStrings)}')

solutions = [binarySearch(explodedStrings[i], targets[i], 0, len(explodedStrings[i])) for i in range(len(explodedStrings))]

print(solutions)

assert solutions == [True, True, True, False]
print("All test cases passed")