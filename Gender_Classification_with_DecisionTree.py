from sklearn.tree import DecisionTreeClassifier #pip install scikit-learn
import pandas as pd                             #pip install pandas
import numpy as np                              #pip install numpy#import os
from sklearn.metrics import accuracy_score      #Decision Tree를 이용해 Test Data의 정확도를 파악하기 위한


#Dataset 불러오기, train_data.csv와 test_data.csv를 입력하여 Data load
train_data = pd.read_csv("C:/Users/whals/Desktop/kakao/train_data.csv",encoding='cp949')
test_data = pd.read_csv("C:/Users/whals/Desktop/kakao/test_data.csv",encoding='cp949')

#Train Dataset 불러오기 (X_train: input, Y_train: output)
X_train = pd.DataFrame(train_data,
        columns=[ '신장', '체중', '허리둘레','HDL콜레스테롤',
                  '혈색소', '혈청크레아티닌','AST', 'ALT',
                  '감마지티피', '흡연상태', '음주여부'])
Y_train= np.array(pd.DataFrame(train_data, columns=['성별코드']))


#Test Dataset 불러오기 (X_test: input, Y_test: output)
X_test = pd.DataFrame(test_data,
        columns=['신장', '체중', '허리둘레','HDL콜레스테롤',
                 '혈색소', '혈청크레아티닌','AST', 'ALT',
                 '감마지티피', '흡연상태', '음주여부'])
Y_test= np.array(pd.DataFrame(test_data, columns=['성별코드']))


#criterion: entropy, max_depth: 4로 설정
decision_Tree = DecisionTreeClassifier(criterion='entropy',max_depth = 8,min_samples_split=5000)

#decision tree 학습
decision_Tree = decision_Tree.fit(X_train, Y_train)

#학습된 모델로 Test, Train Data를 input으로 클래스 예측
Test_pred = decision_Tree.predict(X_test)
Train_pred = decision_Tree.predict(X_train)


#Train 정확도와 Test 정확도를 확인
print('Train Accuracy: %.5f' % accuracy_score(Y_train, Train_pred))
print('Test Accuracy: %.5f' % accuracy_score(Y_test, Test_pred))
