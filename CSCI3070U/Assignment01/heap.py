import random
from socket import J1939_FILTER_MAX
class Heap:
	def __init__(self, A):
		self.size = len(A)
		self.Heap = A
	
	def parent(self, i):
		return i // 2
	
	def left(self, i):
		return (2*i)
	
	def right(self, i):
		return (2*i)+1
	
	def maxHeapify(self, A, i):
		largest = i
		l = self.left(i)
		r = self.right(i)

		if l < self.size and A[l] > A[i]:
			largest = l
		
		if r < self.size and A[r] > A[largest]:
			largest = r
		
		if largest != i:
			A[i], A[largest] = A[largest], A[i] 
			self.maxHeapify(A, largest)
	
	def buildMaxHeap(self):
		startIdx = self.size//2
		for i in range(startIdx, -1, -1):
			self.maxHeapify(self.Heap, i)
	
	def heapMaximum(self):
		return self.Heap[0]
	
	def heapExtractMax(self):
		if self.size < 1:
			print("error heap underflow")
			return
		
		max = self.Heap[0]
		self.Heap[0] = self.Heap[self.size-1]
		self.Heap.pop(self.size-1)
		self.size-=1
		self.maxHeapify(self.Heap, 0)

		return max

	def heapInsert(self, ele):
		self.size += 1
		self.Heap.append(ele)
		curr = self.size-1

		while (self.Heap[curr] > self.Heap[self.parent(curr)] and curr > -1):
			self.Heap[curr], self.Heap[self.parent(curr)] = self.Heap[self.parent(curr)], self.Heap[curr] 
			curr = self.parent(curr)

	def printAsArray(self):
		print(self.Heap)

	def printAsTree(self, array, index, spacing):
		if index > len(array):
			return "ggwp'd"
		self.printAsTree(array, index * 2 + 1, spacing + 1)
		print(('\t' * spacing) + str(array[index-1]))
		self.printAsTree(array, index * 2 , spacing + 1)

def heapSort(A):
	heap = Heap(A)
	n = len(A)
	heap.buildMaxHeap()
	for i in range(n // 2 - 1, -1, -1):
		heap.maxHeapify(A, i)

	for i in range(n - 1, 0, -1):
		(A[i], A[0]) = (A[0], A[i]) 
		heap.size = i
		heap.maxHeapify(A, 0)

arr = [1, 3, 4, 19, 81]
arr1 = [1, 3, 4, 19, 81]
h = Heap(arr)

h.buildMaxHeap()
h.printAsArray()

m = h.heapExtractMax()
print(f"max: {m}")
h.printAsArray()

h.heapInsert(811)
h.printAsArray()

print('----------------------------------------------------')
a = [random.randint(0, 9) for i in range(10)]
print(f'before sort: {a}')
heapSort(a)
print(f'after sort: {a}')
print('---------------------------------------------------')
h1 = Heap(arr1)
h1.buildMaxHeap()
print(f'Array: {arr1}')
h1.printAsTree(arr1, 1, 1)
