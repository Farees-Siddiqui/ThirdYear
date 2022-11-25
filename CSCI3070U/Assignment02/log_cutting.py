import heapq as hq
import bisect

'''
cuts is the list of cuts to be made to the stick
cuts[0] is always going to be 0
cuts[-1] is always going to be the length of the stick
'''
def cutLog(cuts):
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
         cost[i][j] = (cuts[j]-cuts[i]) + min(cost[i][s] + cost[s][j] for s in range(i+1, j))

   
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
   ret = 0
   priorityq = []
   hq.heappush(priorityq, (-n, 0))
   while priorityq:
      length, begin = hq.heappop(priorityq)
      length = -length
      end = begin + length
      if length == 1:
         continue
      it = bisect.bisect_left(cuts, begin + 1)
      it1 = bisect.bisect_left(cuts, end - 1)
      if it == len(cuts) and it1 == len(cuts):
         continue
      best = begin + length / 2.0
      bb = begin + length // 2
      it3 = bisect.bisect_left(cuts, bb)
      if it3 == len(cuts):
         bb = cuts[-1]
         cuts.pop()
      else:
         idx = it3
         best_idx = idx
         if cuts[idx] < end:
            bb = cuts[idx]
         elif idx == 0 or cuts[idx - 1] < begin:
            continue
         else:
            bb = cuts[idx - 1]
            best_idx = idx - 1
         if idx + 1 < len(cuts) and cuts[idx + 1] < end and cuts[idx + 1] > begin:
            if abs(cuts[idx] - best) > abs(cuts[idx + 1] - best):
               best_idx = idx + 1
         if idx - 1 >= 0 and cuts[idx - 1] > begin and cuts[idx - 1] < end:
            if abs(cuts[idx] - best) > abs(cuts[idx - 1] - best):
               best_idx = idx - 1
         bb = cuts[best_idx]
         cuts.pop(best_idx)
      ret += length
      hq.heappush(priorityq, (-(bb - begin), begin))
      hq.heappush(priorityq, (-(end - bb), bb))
   return ret

cost, cuts = cutLog([0, 7, 8, 9, 16])

print(f'Dynamic Programming Approach: (Cost -> {cost} | Optimal Cuts -> {cuts})\nGreedy Approach (Not optimal): {greedyCutLog([7, 8, 9, 16])}')