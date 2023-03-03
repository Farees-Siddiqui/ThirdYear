import torch
import numpy as np
import matplotlib.pyplot as plt 

W = torch.tensor([0., 0.], requires_grad=True)
x = torch.linspace(0, 1, 10)
y_true = 3 * x + torch.sin(6*x) + 1
y_pred = W[0]*x + W[1]
err = torch.linalg.vector_norm(y_pred - y_true) / x.shape[0]
err.backward()
epsilon = 0.01
def init(W):
    with torch.no_grad():
        W.zero_()

def err(W):
    y = W[0] * x + W[1]
    return torch.linalg.norm(y - y_true) / x.shape[0]

def update_step():
    W.grad.zero_()
    e = err(W)
    e.backward()
    with torch.no_grad():
        W.sub_(epsilon * W.grad)
    return e.detach().item()

def report(i):
    with torch.no_grad():
        e = err(W)
        print("[{}] a={:.2f} b={:.2f}, err={:.2f}".format(i, W[0], W[1], e))
        
def report(i):
    with torch.no_grad():
        e = err(W)
        print("[{}] a={:.2f} b={:.2f}, err={:.2f}".format(i, W[0], W[1], e))

N = 2000
e = np.zeros(N)
init(W)
for i in range(N):
    e[i] = update_step()
    if i % (N//10) == 0:
        report(i)
report(N)

(a, b) = W.detach().numpy()

y_pred = a * x + b

class LineFitting(torch.nn.Module):
    def __init__(self):
        super().__init__()
        W = torch.tensor([0,0], dtype=torch.float32)
        self.W = torch.nn.Parameter(W)
        self.length = x
    
    def forward(self, x):
        return self.W[0] * x + self.W[1]
    
"""
The model can be used as a function to evaluate the forward computation
"""
line = LineFitting()

def train(x, y_true, model, LossFn, OptimizerFn, lr, epochs):
    loss = LossFn()
    optimizer = OptimizerFn(model.parameters(), lr=lr)
    for epoch in range(epochs):
        optimizer.zero_grad()
        y = model(x)
        loss(y, y_true).backward()
        optimizer.step()
        if epoch % (epochs//10) == 0:
            with torch.no_grad():
                l = loss(y, y_true).numpy()
                W = next(model.parameters()).numpy()
                print(l, W)
train(x, y_true, line, torch.nn.MSELoss, torch.optim.SGD, 0.1, 10)

def plot(x, y_true, model):
    with torch.no_grad():
        y = model(x)
        plt.plot(x, y_true, '--o')
        plt.plot(x, y, '-');
        plt.show()

plot(x, y_true, line)

class PolyFit(torch.nn.Module):
    def __init__(self, degree):
        super().__init__()
        self.degree = degree
        self.W = torch.nn.Parameter(torch.zeros(degree))
        
    def forward(self, x):
        y = torch.zeros_like(x)
        for i in range(self.degree):
            y += self.W[i] * (x ** i)
        return y
    
poly = PolyFit(5)

train(x, y_true, poly, torch.nn.MSELoss, torch.optim.SGD, 0.05, 100_000)

plot(x, y_true, poly);