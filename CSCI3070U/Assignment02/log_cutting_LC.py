def minCost(n, cuts):
    cuts.append(0)
    cuts.append(n)
    cuts.sort()
    dp = [[0] * len(cuts) for _ in range(len(cuts))]
    for i in range(len(cuts)):
        dp[i][i] = 0
    for i in range(len(cuts) - 1, -1, -1):
        for j in range(i + 1, len(cuts)):
            if j - i == 1:
                dp[i][j] = 0
            else:
                dp[i][j] = min([dp[i][k] + dp[k][j] for k in range(i + 1, j)]) + cuts[j] - cuts[i]
    # Print the optimal order of cuts
    # ex. n = 9, cuts = [5, 6, 1, 4, 2] = 22, cuts -> [4, 6, 5, 2, 1] this is the optimal order of cuts
    printCuts(dp, cuts, 0, len(cuts) - 1)


def printCuts(dp, cuts, i, j):
    # newCuts = [0 for _ in range(len(cuts))]
    global newCuts
    if j - i == 1:
        return
    for k in range(i + 1, j):
        if dp[i][j] == dp[i][k] + dp[k][j] + cuts[j] - cuts[i]:
            print("Cut at: ", cuts[k])
            newCuts.append(cuts[k])
            printCuts(dp, cuts, k, j)
            printCuts(dp, cuts, i, k)
            return
        print(f'newCuts: {newCuts}')

minCost(7, [1, 3, 4, 5])