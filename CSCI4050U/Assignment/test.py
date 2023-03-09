import torch
from torch.utils.data import (
    DataLoader,
    TensorDataset,
    Dataset
)

# given a data set that looks like the following datafram
#      sepal_l  sepal_w  petal_l  petal_w  species
# 0        6.1      2.8      4.7      1.2        1
# 1        5.4      3.9      1.3      0.4        0
# 2        6.5      3.0      5.8      2.2        2
# 3        5.1      3.5      1.4      0.3        0
# 4        5.9      3.0      4.2      1.5        1

# implement a function create_dataset that creates a dataset for this dataframe. the vector should have the following format
# [[sepall, sepalw, petall, petalw], species]

def create_dataset(df):
    dataset = TensorDataset(torch.tensor(df.iloc[:, :-1].values), torch.tensor(df.iloc[:, -1].values))
    return 

# In this unit, you are to implement a neural network module that performs simple linear classification. Namely,

# 𝑦pred=𝑥𝑊+𝑏
 
# Hint:

# Use the built-in nn.Linear(...) as a layer in your module.
# You must name the attribute in the LinearClassifier as linear for you to pass the checkpoint.

the output should look like the following
# ===================================================== │                                                                 │
# │ ╰───────────────────╯ │          Kernel Shape Output Shape  Params  Mult-Adds │                                                                 │
# │                       │ Layer                                                 │                                                                 │
# │                       │ 0_linear       [4, 3]      [32, 3]      15         12 │                                                                 │
# │                       │ ----------------------------------------------------- │                                                                 │
# │                       │                       Totals                          │                                                                 │
# │                       │ Total params              15                          │                                                                 │
# │                       │ Trainable params          15                          │                                                                 │
# │                       │ Non-trainable params       0                          │                                                                 │
# │                       │ Mult-Adds                 12                          │                                                                 │
# │                       │ =====================================================

#do not hard code the parameters for the nn.Linear layer
class LinearClassifier(nn.Module):
    def __init__(self):
        super().__init__()
        self.linear = nn.Linear()
    def forward(self, x):
        return self.linear(x)
    
def train(model: nn.Module, optimizer: Optimizer, dataloader: DataLoader, epochs: int):
    history = []
    accuracy = Accuracy(task='multiclass', num_classes=3)
    for epoch in range(epochs):
        for (x, target) in dataloader:
            pred = model(x)
            loss = cross_entropy(pred, target)
            loss.backward()
            optimizer.step()
            optimizer.zero_grad()
        metrics = {
            'epoch': epoch,
            'loss': loss.item(),
            'acc': accuracy(pred, target).item()
        }
        if epoch % (epochs // 10) == 0:
            print("{epoch}: loss={loss:.4f}, acc={acc:.2f}".format(**metrics))
        history.append(metrics)
    return pd.DataFrame(history)

dataloader = make_dataloader(train_dataset, shuffle=False, batch_size=32)
linearclassifier = LinearClassifier()
# linearclassifier has no parameters
optimizer = Adam(linearclassifier.parameters(), lr=0.01)

history_linear = train(linearclassifier, optimizer, dataloader, 100)
