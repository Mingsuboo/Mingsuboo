import pandas as pd                                 #pip install pandas, csv파일 다루는
import numpy as np                                  #pip install numpy
import torch                                        #ai framework
from torch import nn                                #fc layer 생성을 위한
import torch.optim as optim                         #adam optimizer
import torch.nn.functional as F                     #ReLu 함수 사용
from torch.autograd import Variable                 #파라미터의 변수화
from torch.utils.data import Dataset, DataLoader    #dataset 을 다루기 위함

#Train Dataset 구측, X: input data, Y: output data
class Train_Dataset(Dataset):
    def __init__(self):
        data = pd.read_csv('C:/Users/lab/Desktop/kakao/train_data.csv',encoding = 'cp949')
        #train_data.csv가 저정된 경로를 입력
        X = np.array(pd.DataFrame(data,
            columns=['신장', '체중', '허리둘레', '시력좌', '시력우', '청력좌',
                    '청력우', '수축기혈압', '이완기혈압', '식전혈당', '총콜레스테롤',
                    '트리글리세라이드', 'HDL콜레스테롤', 'LDL콜레스테롤',
                    '혈색소', '요단백', '혈청크레아티닌', 'AST', 'ALT',
                    '감마지티피', '흡연상태', '음주여부', '구강검진수검여부']))
        Y = np.array(pd.DataFrame(data, columns=['연령대코드']))
        self.len = len(data)
        self.x_data = torch.from_numpy(X[:])
        self.y_data = torch.from_numpy(Y[:])
    def __getitem__(self,index):
        return self.x_data[index],self.y_data[index]
    def __len__(self):
        return self.len
    
#Test Dataset 구측, X: input data, Y: output data
class Test_Dataset(Dataset):
    def __init__(self):
        data = pd.read_csv('C:/Users/lab/Desktop/kakao/test_data.csv',encoding = 'cp949')
        # test_data.csv가 저정된 경로를 입력
        X = np.array(pd.DataFrame(data,
            columns=['신장', '체중', '허리둘레', '시력좌', '시력우', '청력좌',
                    '청력우', '수축기혈압', '이완기혈압', '식전혈당', '총콜레스테롤',
                    '트리글리세라이드', 'HDL콜레스테롤', 'LDL콜레스테롤',
                    '혈색소', '요단백', '혈청크레아티닌', 'AST', 'ALT',
                    '감마지티피', '흡연상태', '음주여부', '구강검진수검여부']))
        Y = np.array(pd.DataFrame(data, columns=['연령대코드']))
        self.len = len(data)
        self.x_data = torch.from_numpy(X[:])
        self.y_data = torch.from_numpy(Y[:])
    def __getitem__(self,index):
        return self.x_data[index],self.y_data[index]
    def __len__(self):
        return self.len

#DataLoader를 이용해 Dataset을 pytorch로 학습시킬 수 있는 형태로 변환, Batch Size를 9000으로 지정,
# Dataset size가 900,000이기 때문에 100 iter 당 1 epoch
testdataset = Test_Dataset()
test_loader = DataLoader(dataset=testdataset, batch_size=9000, shuffle=True)
traindataset = Train_Dataset()
train_loader = DataLoader(dataset=traindataset, batch_size=9000, shuffle=True)

#print(traindataset.__len__(),testdataset.__len__())

#DNN모델 Class, fc connecter Layer를 이용 Depth에 맞게 활용
class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.h1 = nn.Linear(23,50)
        self.h2 = nn.Linear(50,50)
        #self.h3 = nn.Linear(50, 50)
        #self.h4 = nn.Linear(50, 50)
        #self.h5 = nn.Linear(50, 50)
        #self.h6 = nn.Linear(50, 50)
        self.h7 = nn.Linear(50,7)

    def forward(self, x):
        x = F.relu(self.h1(x))
        x = F.relu(self.h2(x))
        #x = F.relu(self.h3(x))
        #x = F.relu(self.h4(x))
        #x = F.relu(self.h5(x))
        #x = F.relu(self.h6(x))
        return self.h7(x)


#Net() 클래스 생성
net = Net()
#float을 input으로 받기 때문
net = net.float()
#loss function을 CrossEntropy로 선언
criterion = nn.CrossEntropyLoss()
#optimizer는 Adam, Learning Rate:0.001
optimizer = optim.Adam(net.parameters(),lr=0.001)

#Train Dataset을 이용해 모델을 학습시키는 함수
def train(epoch):
    net.train()
    for batch_idx, (data, target) in enumerate(train_loader):
        data,target = Variable(data), Variable(target)
        optimizer.zero_grad()
        target = target.squeeze(1)
        output = net(data.float())
        loss = criterion(output,target)
        loss.backward()
        optimizer.step()
        if batch_idx % 10 == 0:
            print('Train Epoch: {} [{}/{} ({:.0f}%)]\tLoss: {:.6f}'.format(
                epoch, batch_idx*len(data), len(train_loader.dataset),
                100.*batch_idx/len(train_loader),loss.data
            ))

#Test Dataset을 이용해 학습된 모델의 정확도를 측정
def test():
    net.eval()
    test_loss=0
    correct =0
    for data, target in test_loader:
        data, target = Variable(data), Variable(target)
        target = target.squeeze(1)
        output=net(data.float())
        test_loss +=criterion(output, target).data
        pred = output.data.max(1,keepdim=True)[1]
        correct += pred.eq(target.data.view_as(pred)).cpu().sum()

    test_loss /= len(test_loader.dataset)
    print('\nTest set: avg loss: {:.4f},  acc:{}/{} ({:.0f}%)\n'.format(
        test_loss,correct, len(test_loader.dataset), 100.*correct/len(test_loader.dataset)
    ))

#epoch을 지정하여 학습진행
for epoch in range(1,200):
    train(epoch)
    test()
