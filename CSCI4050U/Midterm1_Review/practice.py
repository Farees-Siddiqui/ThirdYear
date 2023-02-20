import numpy as np
import torch
import matplotlib.pyplot as plt

def f(x):
    return x[0] ** 2 + 2 * x[1] ** 2

def GD(x0, step_size, num_steps):
    x = torch.tensor(x0, requires_grad=True, dtype=torch.float32)
    history = [[x.detach().numpy()[0], x.detach().numpy()[1], f(x.detach().numpy())]]
    for i in range(num_steps):
        y = f(x)
        y.backward()
        with torch.no_grad():
            dx = step_size * x.grad
            x -= dx
        # detached = x.detach()
        curr = [x.detach().numpy()[0], x.detach().numpy()[1], f(x.detach().numpy())]
        history.append(curr)
        # print(curr)
        x.grad.zero_()
    return torch.round(torch.tensor(history, dtype=torch.float32), decimals=1)  

def GD_momentum(x0, step_size, beta, num_steps):
    x = torch.tensor(x0, requires_grad=True, dtype=torch.float32)
    history = [[x.detach().numpy()[0], x.detach().numpy()[1], f(x.detach().numpy())]]
    dx = torch.zeros_like(x)
    for i in range(num_steps):
        y = f(x)
        y.backward()
        with torch.no_grad():
            dx = step_size * x.grad + beta * dx
            x -= dx
        curr = [x.detach().numpy()[0], x.detach().numpy()[1], f(x.detach().numpy())]
        history.append(curr)
        # print(curr)
        x.grad.zero_()
    return torch.round(torch.tensor(history, dtype=torch.float32), decimals=1)  

# history_m = GD_momentum((-5, -2), step_size=0.02, beta=0.7, num_steps=20)
# history = GD((-5, -2), step_size=0.02, num_steps=20)

"""Testing GD with large step size"""
history_m = GD_momentum((-5, -2), step_size=0.48, beta=0.7, num_steps=20)
history = GD((-5, -2), step_size=0.48, num_steps=20)

xs = np.linspace(-6, 4, 100)
ys = np.linspace(-6, 4, 100)

xx, yy = np.meshgrid(xs, ys)
coord = np.concatenate([xx[:,:,None], yy[:,:,None]], axis=-1)
coord = coord.reshape(-1, 2).T

z = f(coord)
z = z.reshape(100,100)

plt.set_cmap(plt.get_cmap('jet'))
plt.contourf(xx, yy, z, levels=100)
ax = plt.gca()
ax.set_aspect('equal');

plt.contourf(xx, yy, z, levels=100)
plt.plot(history_m[:, 0], history_m[:, 1], '-o', color='yellow', markersize=5)
plt.text(history_m[-1, 0], history_m[-1, 1], '%.2f' % history_m[-1, 2], color='yellow')

plt.plot(history[:, 0], history[:, 1], '-o', color='red', markersize=5)
plt.text(history[-1, 0], history[-1, 1], '%.2f' % history[-1, 2], color='red')

plt.gca().set_aspect('equal');
plt.show()