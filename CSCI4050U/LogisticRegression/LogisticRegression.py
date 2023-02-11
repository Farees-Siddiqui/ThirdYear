import numpy as np
import matplotlib.pyplot as plt
from   sklearn import datasets
import pandas as pd
import torch
import torch.nn as nn
from torch.nn.functional import binary_cross_entropy

class LogisticRegression(nn.Module):
    def __init__(self, features=2):
        super().__init__()
        self.w = nn.Parameter(torch.randn(size=(features,)))
        self.b = nn.Parameter(torch.randn(size=()))
        self.activation = nn.Sigmoid()
    def forward(self, x):
        return self.activation(x @ self.w + self.b)

iris = datasets.load_iris()
dataset = pd.DataFrame(
    iris['data'],
    columns=['sepal_length', 'sepal_width', 'petal_length', 'petal_width']
)
dataset['species'] = iris['target']
dataset = dataset.sample(frac=1)
print(dataset.head())

df = dataset[(dataset.species == 0) | (dataset.species == 1)]
x_df = df[['sepal_length', 'sepal_width']]
y_df = df['species']

# c = ['blue' if s == 0 else 'red' for s in y_df]
# plt.scatter(x_df['sepal_length'], x_df['sepal_width'], c=c)
# plt.show()

model = LogisticRegression()
x_input = torch.tensor(x_df.values, dtype=torch.float32)
y_true = torch.tensor(y_df, dtype=torch.float32)
print(model(x_input[:5]))

with torch.no_grad():
    p = model(x_input)
    L = binary_cross_entropy(p, y_true, reduction='none').numpy()
    df = pd.DataFrame({
        'y_i': y_true,
        'p_i': p,
        'L_i': L,
    })
    
print(df.head)

model = LogisticRegression()
loss = binary_cross_entropy
optimizer = torch.optim.SGD(model.parameters(), lr=0.1)
epochs = 100

for epoch in range(epochs):
    optimizer.zero_grad()
    L = loss(model(x_input), y_true)
    L.backward()
    optimizer.step()
    if epoch % (epochs // 10) == 0:
        with torch.no_grad():
            print(L.numpy())
            
print(model.w, model.b)