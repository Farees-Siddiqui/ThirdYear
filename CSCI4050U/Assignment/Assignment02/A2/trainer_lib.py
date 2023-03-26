import itertools
import time
import torch
from torch import (nn, optim)
import pandas as pd
import numpy as np


class Trainer:
    def __init__(self, model, train_dataloader, val_dataloader):
        self.model = model
        self.train_dataloader = train_dataloader
        self.val_dataloader = val_dataloader
        self.optimizer = optim.Adam(model.parameters())
        self.loss = nn.CrossEntropyLoss()

    def categorical_accuracy(self, y_out, target):
        pred = y_out.argmax(axis=1)
        succ = (pred == target).sum().item()
        total = len(target)
        return succ/total

    def train_one_epoch(self, max_batches=None):
        l_list = []
        acc_list = []
        for (i, (xs, targets)) in enumerate(itertools.islice(self.train_dataloader, 0, max_batches)):
            # complete the following
            y_out = self.model(xs)
            loss = self.loss(y_out, targets)
            self.optimizer.zero_grad()
            loss.backward()
            self.optimizer.step()
            acc = self.categorical_accuracy(y_out, targets)
            l_list.append(loss.item())
            acc_list.append(acc)
        return np.mean(l_list), np.mean(acc_list)

    def val_one_epoch(self):
        l_list = []
        acc_list = []
        with torch.no_grad():
            # complete the following
            for (xs, targets) in self.val_dataloader:
                y_out = self.model(xs)
                loss = self.loss(y_out, targets)
                acc = self.categorical_accuracy(y_out, targets)
                l_list.append(loss.item())
                acc_list.append(acc)
        return np.mean(l_list), np.mean(acc_list)

    def train(self, epochs, max_batches=None):
        history = {
            'train_loss': [],
            'train_accuracy': [],
            'val_loss': [],
            'val_accuracy': [],
            'epoch_duration': [],
        }

        start0 = time.time()

        for epoch in range(epochs):
            start = time.time()
            train_loss, train_acc = self.train_one_epoch(max_batches)

            val_loss, val_acc = self.val_one_epoch()

            duration = time.time() - start
            history['train_loss'].append(train_loss)
            history['train_accuracy'].append(train_acc)
            history['val_loss'].append(val_loss)
            history['val_accuracy'].append(val_acc)
            history['epoch_duration'].append(duration)

            print("[%d (%.2fs)]: train_loss=%.2f train_acc=%.2f, val_loss=%.2f val_acc=%.2f" % (
                epoch, duration, train_loss, train_acc, val_loss, val_acc))

        duration0 = time.time() - start0
        print("== Total training time %.2f seconds ==" % duration0)

        return pd.DataFrame(history)

    def reset(self):
        for layer in self.model.children():
           if hasattr(layer, 'reset_parameters'):
               layer.reset_parameters()
