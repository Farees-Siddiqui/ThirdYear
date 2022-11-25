import heapq as hq
import bisect

'''
November 15, 2022
Farees Siddiqui - 100780513
Nicholas Kissoon - 100742790
'''

'''
cuts is the list of cuts to be made to the stick
cuts[0] is always going to be 0
cuts[-1] is always going to be the length of the stick
'''
def cutLog(cuts): # [7, 8, 9, 16]
   n = cuts.pop()
   res = []
   cuts = sorted(cuts) + [n]
   m = len(cuts)
   cost = [[0]*m for _ in range(m)]

   for k in range(2, m):
      for i in range(m):
         j = i + k
         if j >= m:
            continue
         cost[i][j] = (cuts[j]-cuts[i]) + min(cost[i][k] + cost[k][j] for k in range(i+1, j))

   
   return cost[0][m-1], printCuts(cost, cuts, 0, m-1, res)


# implement the printCuts function to print the optimal order of cuts
def printCuts(cost, cuts, i, j, res):
   if j - i == 1:
      return
   for k in range(i+1, j):
      if cost[i][j] == cost[i][k] + cost[k][j] + cuts[j] - cuts[i]:
         # print("Cut at: ", cuts[k])
         res.append(cuts[k])
         printCuts(cost, cuts, k, j, res)
         printCuts(cost, cuts, i, k, res)
         return res

def greedyCutLog(cuts):
   n = cuts.pop()
   cuts.sort()
   if len(cuts) <= 1:
      return n
   res= 0
   priorityq = []
   hq.heappush(priorityq, (-n, 0))
   while priorityq:
      length, beginCurPiece = hq.heappop(priorityq)
      length = -length
      endCurPiece = beginCurPiece + length
      if length == 1:
         continue
      idxCutRight= bisect.bisect_left(cuts, beginCurPiece + 1)
      idxCutLeft= bisect.bisect_left(cuts, endCurPiece - 1)
      if idxCutRight== len(cuts) and idxCutLeft== len(cuts):
         continue
      bestCut = beginCurPiece + length / 2.0
      currCut = beginCurPiece + length // 2
      it3 = bisect.bisect_left(cuts, currCut)
      if it3 == len(cuts):
         currCut = cuts[-1]
         cuts.pop()
      else:
         idx = it3
         bestCut_idx = idx
         if cuts[idx] < endCurPiece:
            currCut = cuts[idx]
         elif idx == 0 or cuts[idx - 1] < beginCurPiece:
            continue
         else:
            currCut = cuts[idx - 1]
            bestCut_idx = idx - 1
         if idx + 1 < len(cuts) and cuts[idx + 1] < endCurPiece and cuts[idx + 1] > beginCurPiece:
            if abs(cuts[idx] - bestCut) > abs(cuts[idx + 1] - bestCut):
               bestCut_idx = idx + 1
         if idx - 1 >= 0 and cuts[idx - 1] > beginCurPiece and cuts[idx - 1] < endCurPiece:
            if abs(cuts[idx] - bestCut) > abs(cuts[idx - 1] - bestCut):
               bestCut_idx = idx - 1
         currCut = cuts[bestCut_idx]
         cuts.pop(bestCut_idx)
      res+= length
      hq.heappush(priorityq, (-(currCut - beginCurPiece), beginCurPiece))
      hq.heappush(priorityq, (-(endCurPiece - currCut), currCut))
   return res

cost, cuts = cutLog([0, 7 ,8, 9, 16])

print(f'Dynamic Programming Approach: (Cost -> {cost} | Optimal Cuts -> {cuts})\nGreedy Approach (Not optimal): {greedyCutLog([0, 7 ,8, 9, 16])}')
