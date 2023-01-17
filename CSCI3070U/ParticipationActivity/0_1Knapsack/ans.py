# 0-1 knapsack

def Knapsack01(weights, profits, maxWeight):
    """From pseudo code (Dynamic programming II, slide 36)
    
    w1..n = weights, b1:n = profits, W = maxWeight
    
    Args:
        weights (list): array of weights for each object
        profits (list): array of profits for each object
        maxWeight (int): max weight of knapsack
    """    
    n = len(weights)
    B = [[0 for _ in range(maxWeight+1)] for _ in range(n)]
    
    for w in range(maxWeight):
        B[0][w] = 0
        
    for i in range(n):
        B[i][0] = 0
    
    for i in range(n):
        for w in range(maxWeight):
            if weights[i] <= w:
                if profits[i] + B[i-1][w-weights[i]] > B[i-1][w]:
                    B[i][w] = profits[i] + B[i-1][w - weights[i]]
                else:
                    B[i][w] = B[i-1][w]
            else:
                B[i][w] = B[i-1][w]
    return B[n-1][maxWeight-1]

print(Knapsack01([2, 3, 4, 5], [3, 4, 5, 6], 5))