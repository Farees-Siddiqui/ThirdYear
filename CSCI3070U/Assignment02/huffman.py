import heapq as hq

class Node:
    def __init__(self, freq, symbol, left=None, right=None):
        self.freq = freq
        self.symbol = symbol
        self.left = left
        self.right = right
        self.huff = ''
    
    def __lt__(self, x):
        return self.freq < x.freq
    
def getFreqFromFile(fileName):
    freq = {}
    with open(fileName, 'r') as f:
        for line in f:
            for char in line:
                if char in freq:
                    if char == ' ':
                        freq["SPACE"] += 1
                    elif char == '\n':
                        freq["NEWLINE"] += 1
                    else:
                        freq[char] += 1
                else:
                    if char == ' ':
                        freq["SPACE"] = 1
                    elif char == '\n':
                        freq["NEWLINE"] = 1
                    else:
                        freq[char] = 1     
    return freq

def huffman(C):
    Q = []
    for key in C:
        hq.heappush(Q, Node(C[key], key))
    while len(Q) > 1:
        x = hq.heappop(Q)
        y = hq.heappop(Q)
        z = Node(x.freq + y.freq, None, x, y)
        x.huff = 0
        y.huff = 1
        hq.heappush(Q, z)
    return Q[0]

def printCodes(node, code=''):
    new = code + str(node.huff)
    node.huff = new
    if node.left:
        printCodes(node.left, node.huff)
    if node.right:
        printCodes(node.right, node.huff)
    if not node.left and not node.right:
        print(f'{node.symbol}: \t{node.huff} \t-> {node.freq}')

def getEncodedSize(root):
    stack = []
    stack.append(root)
    sum = 0
    while len(stack) > 0:
        node = stack.pop()
        if node.symbol != None:
            sum += node.freq * len(node.huff)
        if node.right != None:
            stack.append(node.right)
        if node.left != None:
            stack.append(node.left)
    return sum

def getFileSize(freq):
    chars = list(freq.keys())
    frequencies = list(freq.values())
    print(f'chars: {chars} | frequencies: {frequencies}')
    res = {}
    for i in range(len(chars)):
        print(f'{chars[i]}: {frequencies[i]}')
        res[chars[i]] = len(''.join(format(ord(chars[i]), '08b'))) * frequencies[i]
    return sum(res.values())
    

frequencies = getFreqFromFile('huffman.txt')
Q = huffman(frequencies)
printCodes(Q)
print(f'Before Huffman Encoding: {getFileSize(frequencies)} bits -> After Encoding: {getEncodedSize(Q)} bits')
