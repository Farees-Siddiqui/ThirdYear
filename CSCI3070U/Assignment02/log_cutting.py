def cutLog(n, cuts):
   res = []
   cuts = [0] + sorted(cuts) + [n]
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
         print("Cut at: ", cuts[k])
         res.append(cuts[k])
         printCuts(cost, cuts, k, j, res)
         printCuts(cost, cuts, i, k, res)
         return res

print(cutLog(7, [1, 3, 4, 5]))