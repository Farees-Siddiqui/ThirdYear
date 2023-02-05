import numpy as np
import torch
import matplotlib.pyplot as plt

# This is the potential function, later this will become the loss function
def f(x):
    return x[0] ** 2 + 2 * x[1] ** 2

# gradient of f(x)
def g(x):
    return np.array([2*x[0], 4*x[1]])

xs = np.linspace(-6, 4, 100)
ys = np.linspace(-6, 4, 100)

xx, yy = np.meshgrid(xs, ys)

coord = np.concatenate([xx[:,:,None], yy[:,:,None]], axis=-1)
coord = coord.reshape(-1, 2).T

z = f(coord)
z = z.reshape(100, 100)

# plt.set_cmap(plt.get_cmap('jet'))
# plt.contourf(xx, yy, z, levels=100)
# ax = plt.gca()
# ax.set_aspect('equal')



'''
the most basic version of Gradient Descent Algorithm

init x to some location
for i in range(num_steps):
    grad = (gradient(f))(x)
    x = x - step * grad

'''

#
# the GD algorithm that tracks the path
#
def GD(x0, step, num_steps):
    x = np.array(x0)
    history = [[x[0], x[1], f(x)]]
    
    for i in range(num_steps):
        grad = g(x)
        dx = step * grad
        x = x - dx
        history.append([x[0], x[1], f(x)])
    return np.array(history)

#
# Momentum based GD
#
def GD_momentum(x0, step, beta, num_steps):
    x = np.array(x0)
    dx = np.zeros_like(x)
    history = [[x[0], x[1], f(x)]]
    
    for i in range(num_steps):
        grad = g(x)
        dx = step * grad + beta * dx
        x = x - dx
        history.append([x[0], x[1], f(x)])
    return np.array(history)

history_m = GD_momentum((-5, -2), step=0.48, beta=0.7, num_steps=20)
history = GD((-5, -2), step=0.02, num_steps=20)

history.round(1)
history_m.round(1)

# plt.set_cmap(plt.get_cmap('jet'))
plt.contourf(xx, yy, z, levels=100)
plt.plot(history_m[:, 0], history_m[:, 1], '-o', color='yellow', markersize=5)
plt.text(history_m[-1, 0], history_m[-1, 1], '%.2f' % history_m[-1, 2], color='yellow')

plt.plot(history[:, 0], history[:, 1], '-o', color='red', markersize=5)
plt.text(history[-1, 0], history[-1, 1], '%.2f' % history[-1, 2], color='red')

plt.gca().set_aspect('equal');
plt.show()