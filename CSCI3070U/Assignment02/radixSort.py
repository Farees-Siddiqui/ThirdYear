'''
November 15, 2022
Farees Siddiqui - 100780513
Nicholas Kisson - 100742790
'''

import random

# stable version of the insertion sort algorithm
def stableInsertionSort(array, digit):
    for i in range(1, len(array)):
        key = array[i]
        j = i - 1
        while j >= 0 and getDigit(array[j], digit) > getDigit(key, digit):
            array[j + 1] = array[j]
            j -= 1
        array[j + 1] = key
    return array

# gets the nth digit of a number
def getDigit(number, digit):
    working = number // 10**(digit-1);
    return working % 10;

# radix sort
def radixSort(array):
    for i in range(1, 7):
        array = stableInsertionSort(array, i)

array = [random.randint(0, 999999) for i in range(10)]
print(f'Unsorted: {array}')
radixSort(array)
print(f'Sorted: {array}')
