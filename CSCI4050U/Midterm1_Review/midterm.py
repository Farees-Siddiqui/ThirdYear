import numpy as np
import torch

def f(x, y):
    return torch.cos(x)**2 + torch.sin(y)**2

def dist(x, y):
    z = f(x, y)
    return torch.sqrt(x**2 + y**2 + z**2)

def train(x0, y0, epochs, lr):
    x = torch.tensor(x0, requires_grad=True)
    y = torch.tensor(y0, requires_grad=True)
    history = [[x.item(), y.item(), f(x,y), dist(x, y)]]    
    for i in range(epochs):
        d = dist(x, y)
        d.backward()
        with torch.no_grad():
            x -= lr * x.grad
            y -= lr * y.grad
        tmp = [x.item(), y.item(), f(x,y), dist(x, y)]
        # print(f'Current: {tmp}')
        history.append(tmp)
        x.grad.zero_()
        y.grad.zero_()
    return torch.round(torch.tensor(history), decimals=2)

hist =train(1.0, 1.0, 10, 0.3)
print("--------Train----------")
torch.set_printoptions(sci_mode=False)
print(hist)