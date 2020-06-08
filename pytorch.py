import torch #conda install pytorch-cpu torchvision-cpu -c pytorch
import torchvision
import torchvision.transforms as transforms
from torch.autograd import Variable
import torch.nn as nn
import torch.nn.functional as F

import matplotlib.pyplot as plt
import numpy as np
import torch.optim as optim
import json
import os

transform = transforms.Compose([
    transforms.Resize((224, 224)),
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5)),
])

dataset = torchvision.datasets.ImageFolder(root='./DATA/styleEleganceActive',  transform=transform)

trainset, valset= torch.utils.data.random_split(dataset, [45209, 5023])


trainloader = torch.utils.data.DataLoader(trainset, batch_size=32, shuffle=True)
testloader =torch.utils.data.DataLoader(valset, batch_size=32, shuffle=True)

class VGGNet(nn.Module):
    def __init__(self):
        super(VGGNet, self).__init__()
        self.conv = nn.Sequential(
            #3 224 128
            nn.Conv2d(3, 64, 3, padding=1),nn.LeakyReLU(0.2),
            #nn.Conv2d(64, 64, 3, padding=1),nn.LeakyReLU(0.2),
            nn.MaxPool2d(2, 2),
            #64 112 64
            nn.Conv2d(64, 128, 3, padding=1),nn.LeakyReLU(0.2),
            #nn.Conv2d(128, 128, 3, padding=1),nn.LeakyReLU(0.2),
            nn.MaxPool2d(2, 2),
            #128 56 32
            nn.Conv2d(128, 256, 3, padding=1),nn.LeakyReLU(0.2),
            nn.Conv2d(256, 256, 3, padding=1),nn.LeakyReLU(0.2),
            #nn.Conv2d(256, 256, 3, padding=1),nn.LeakyReLU(0.2),
            nn.MaxPool2d(2, 2),
            #256 28 16
            nn.Conv2d(256, 512, 3, padding=1),nn.LeakyReLU(0.2),
            nn.Conv2d(512, 512, 3, padding=1),nn.LeakyReLU(0.2),
            #nn.Conv2d(512, 512, 3, padding=1),nn.LeakyReLU(0.2),
            nn.MaxPool2d(2, 2),
            #512 14 8
            nn.Conv2d(512, 512, 3, padding=1),nn.LeakyReLU(0.2),
            nn.Conv2d(512, 512, 3, padding=1),nn.LeakyReLU(0.2),
            #nn.Conv2d(512, 512, 3, padding=1),nn.LeakyReLU(0.2),
            nn.MaxPool2d(2, 2)
        )
        #512 7 4

        self.avg_pool = nn.AvgPool2d(7)
        #512 1 1
        self.classifier = nn.Linear(512, 1000)
        """
        self.fc1 = nn.Linear(512*2*2,4096)
        self.fc2 = nn.Linear(4096,4096)
        self.fc3 = nn.Linear(4096,10)
        """

    def forward(self, x):
        #print(x.size())
        features = self.conv(x)
        #print(features.size())
        x = self.avg_pool(features)
        #print(x.size())
        x = x.view(features.size(0), -1)
        #print(x.size())
        x = self.classifier(x)
        #x = self.softmax(x)
        return x



net = VGGNet()



criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(net.parameters(),lr=0.00001)

def train(epoch):
    net.train()
    for batch_idx, (data, target) in enumerate(trainloader):
        data,target = Variable(data), Variable(target)
        optimizer.zero_grad()
        output = net(data)
        loss = criterion(output,target)
        loss.backward()
        optimizer.step()
        if batch_idx % 10 == 0:
            print('Train Epoch: {} [{}/{} ({:.0f}%)]\tLoss: {:.6f}'.format(
                epoch, batch_idx*len(data), len(trainloader.dataset),
                100.*batch_idx/len(trainloader),loss.data
            ))
def test():
    net.eval()
    test_loss=0
    correct =0
    i=0
    for data, target in testloader:
        i+=1
        print(i)
        data, target = Variable(data), Variable(target)
        output=net(data)

        test_loss +=criterion(output, target).data

        pred = output.data.max(1,keepdim=True)[1]
        correct += pred.eq(target.data.view_as(pred)).cpu().sum()

    test_loss /= len(testloader.dataset)
    print('\nTest set: avg loss: {:.4f},  acc:{}/{} ({:.0f}%)\n'.format(
        test_loss,correct, len(testloader.dataset), 100.*correct/len(testloader.dataset)
    ))

for epoch in range(1,75):
    train(epoch)
    test()