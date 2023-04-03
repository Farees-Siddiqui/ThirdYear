import torch
import torch.nn as nn
from torch.utils.data import (DataLoader, TensorDataset)

def test_saved_model(model = None):
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

    test_dataset = torch.load('./test_dataset.npz')
    if model is None:
        print("Loading from mymodel.pt")
        model = torch.load('./mymodel.pt').to(device)
    loss = nn.CrossEntropyLoss()
    dataloader = DataLoader(test_dataset, batch_size=128, shuffle=True)
    acc = 0
    with torch.no_grad():
        for xs, targets in dataloader:
            xs, targets = xs.to(device), targets.to(device)
            ys = model(xs)
            acc += (ys.argmax(axis=1) == targets).sum().item()
    acc = acc / len(test_dataset) * 100
    print("Saved model has test accuracy = %.2f" % acc)

