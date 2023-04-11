# create a LSTM architecture that can be used to predict whether or not an app will be used in the next 60seconds

import torch
import torch.nn as nn

class MyModel(nn.Module):
    def __init__(self, input_size, hidden_size, num_layers, num_classes):
        super(MyModel, self).__init__()
        self.num_layers = num_layers
        self.hidden_size = hidden_size
        self.lstm = nn.LSTM(input_size, hidden_size, num_layers, batch_first=True)
        self.fc = nn.Linear(hidden_size, num_classes)
    
    def forward(self, x):
        
        # Forward propagate LSTM
        out, _ = self.lstm(x)