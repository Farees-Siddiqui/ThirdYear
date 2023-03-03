import numpy as np
import torch
import matplotlib.pyplot as plt
"""Consider a line defined by y = 3x.  We want to compute the projection of [1, 1] on the line in two ways."""
""" 1. Use the projection method."""
def line(x):
    return np.array([x, 3*x])

def proj(u, v):
    v = v/np.sqrt(v @ v)
    return u @ v * v

u = np.array([1,1])

v = np.array([3.5, 10.5]) # this is just a random point that lies on the line y=3x. f(3.5) = 3*(3.5) = 10.5
w = proj(u,v)
print(f'Using projection method: {w}')

"""Using Gradient Descent"""
def f(x):
    return torch.sqrt((x - 1) ** 2 + (3*x - 1) ** 2)

def GD(x0, step_size, num_steps):
    x = torch.tensor(x0, requires_grad=True, dtype=torch.float32)
    history = [[x.item(), 3*x.item(), f(x)]]
    for i in range(num_steps):
        y = f(x)
        y.backward()
        with torch.no_grad():
            dx = step_size * x.grad
            x -= dx
        # detached = x.detach()
        curr = [x.item(), 3*x.item(), f(x)]
        history.append(curr)
        # print(curr)
        x.grad.zero_()
    return torch.round(torch.tensor(history, dtype=torch.float32), decimals=1)  

hist = GD(0.0, step_size=0.1, num_steps=20)
print(f'Using Gradient Descent:  {hist[-1][:2].detach().numpy()}')

"""Consider the following set of predictions adn targets"""
"""
prob of rain   prob of sun   actual weather
0.8               0.2               sun
0.6               0.4               sun
0.8               0.2               rain
0.2               0.8               rain

Compute the mean binary cross entropy loss. Show the pytorch code.
You must implement your own binary cross entropy loss function
"""

p_pred = torch.tensor([0.2, 0.4, 0.2, 0.8])
y_true = torch.tensor([1, 1, 0, 0])

def binary_cross_entropy_loss(p, y):
    return -y*torch.log(p) - (1-y)*torch.log(1-p)

crossentropies = binary_cross_entropy_loss(p_pred, y_true)
print(f'Cross Entropies: {crossentropies}')
print(f'Mean Binary Cross Entropy Loss: {torch.sum(crossentropies)/4}')