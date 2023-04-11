import torch
import matplotlib.pyplot as plt
import numpy as np

x = torch.linspace(0, 1, 100) # 100 evenly spaced points from 0 to 1
y_true = 3 * x + torch.sin(6 * x) +  1

plt.plot(x, y_true, '--o', )

W = torch.tensor([0., 0.], requires_grad=True)

y_pred = W[0]*x + W[1]
err = torch.linalg.vector_norm(y_pred - y_true) / x.shape[0]

print(f'Error: {err}')
print(f'W: {W}')
print(f'err.backward(): {err.backward()}')


grad = W.grad
print(f'Gradient: {grad}')

epsilon = 0.01 # learning rate
with torch.no_grad():
    W.sub_(epsilon * grad)

print(f'W: {W}')

#
# Previous error is 0.8162
#

y_pred = W[0]*x + W[1]
err = torch.linalg.vector_norm(y_pred - y_true) / x.shape[0]
print(f'Error: {err}')


W.grad.zero_()

err.backward()
grad = W.grad

with torch.no_grad():
    W.sub_(epsilon * grad)

print(f'W: {W}')

#
# Previous error is 0.8150
#

y_pred = W[0]*x + W[1]
err = torch.linalg.vector_norm(y_pred - y_true) / x.shape[0]
print(f'err: {err}')

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

# plt.subplot(2,1,1)
# plt.plot(x, y_true, '--')
# plt.plot(x, y_pred, '-');

# plt.subplot(2,1,2)
# plt.plot(e)
# plt.show()
print("------------------------------------")
class LineFitting(torch.nn.Module):
    def __init__(self):
        super().__init__()
        W = torch.tensor([0, 0], dtype=torch.float32)
        self.W = torch.nn.Parameter(W)
        self.length = x
    def forward(self, x):
        return self.W[0] * x + self.W[1]

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

def plot(x, y_true, model):
    with torch.no_grad():
        y = model(x)
        plt.plot(x, y_true, '--o')
        plt.plot(x, y, '-')
        plt.show()

#
# The model can be used as a function to evaluate the forward computation
#

# line = LineFitting()
# line(x)

poly = PolyFit(5)

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
train(x, y_true, poly, torch.nn.MSELoss, torch.optim.SGD, 0.05, 100_000)


plot(x, y_true, poly)