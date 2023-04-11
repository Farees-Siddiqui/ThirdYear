import torch
import matplotlib.pyplot as plt

'''
PyTorch is a drop-in replacement of NumPy with several key extensions.

- PyTorch supports autograd - a feature of numerical libraries that automatically generates gradients using a technique known as backpropagation.

- PyTorch supports hardware acceleration so that the matrix computations can be carried out efficiently on 
specialized hardwares such as Graphics Processing Units (GPU) or Tensor Processing Units (TPU) when they are available.
'''

# Drop in replacement of NumPy
def f(x):
    return x[0] ** 2 + 2 * x[1] ** 2

xs = torch.linspace(-6, 4, 100)
ys = torch.linspace(-6, 4, 100)

xx, yy = torch.meshgrid(xs, ys, indexing=None)
coord = torch.concatenate([xx[:,:,None], yy[:,:,None]], axis=-1)
coord = coord.reshape(-1, 2).T

z = f(coord)
z = z.reshape(100,100)

plt.set_cmap(plt.get_cmap('jet'))
plt.contourf(xx, yy, z, levels=100)
ax = plt.gca()
ax.set_aspect('equal')
plt.show()

'''
Converting torch.tensor to numpy
x = torch.tensor([1., 2.])
x.numpy
'''