import pandas as pd #pip install pandas
import numpy as np
csv_file_path='C:/Users/whals/Desktop/kakao/NHIS_OPEN_GJ_2017.csv'
#건강검진정보 데이터 dataset.csv파일을 load
data = pd.read_csv(csv_file_path,
                   encoding='cp949')

#성별과 나이와 무관한 데이터 제거
del data["기준년도"]
del data["시도코드"]
del data["데이터공개일자"]

#누락되어 없는 칼럼 데이터 제거
del data["치아우식증유무"]
del data["결손치유무"]
del data["치아마모증유무"]
del data["제3대구치(사랑니)이상"]
del data["치석"]

#가독성을 위해 칼럼의 이름 재정의
data.columns=(['가입자일련번호', '성별코드', '연령대코드', '신장', '체중', '허리둘레',
                '시력좌', '시력우', '청력좌', '청력우', '수축기혈압', '이완기혈압',
               '식전혈당','총콜레스테롤', '트리글리세라이드', 'HDL콜레스테롤',
               'LDL콜레스테롤', '혈색소','요단백', '혈청크레아티닌','AST', 'ALT',
               '감마지티피', '흡연상태', '음주여부','구강검진수검여부'])


#연령대 표현을 (코드(5살 단위) -> 코드(10살 단위))으로 변환
#0:20대, 1:30대, 2:40대, 3:50대, 4:60대, 5:70대, 6:80대(이상)

for i in range(5,19):
    data.연령대코드 = data.연령대코드.replace(i,int((i-5)/2))

#입력되지 않아 nan으로 표현되는 값 -> -1로 변환
data.신장 = data.신장.replace(np.nan,-1)
data.체중 = data.체중.replace(np.nan,-1)
data.허리둘레 = data.허리둘레.replace(np.nan,-1)
data.시력좌 = data.시력좌.replace(np.nan,-1)
data.시력우 = data.시력우.replace(np.nan,-1)
data.청력좌 = data.청력좌.replace(np.nan,-1)
data.청력우 = data.청력우.replace(np.nan,-1)
data.수축기혈압 = data.수축기혈압.replace(np.nan,-1)
data.이완기혈압 = data.이완기혈압.replace(np.nan,-1)
data.식전혈당 = data.식전혈당.replace(np.nan,-1)
data.총콜레스테롤 = data.총콜레스테롤.replace(np.nan,-1)
data.트리글리세라이드 = data.트리글리세라이드.replace(np.nan,-1)
data.HDL콜레스테롤 = data.HDL콜레스테롤.replace(np.nan,-1)
data.LDL콜레스테롤 = data.LDL콜레스테롤.replace(np.nan,-1)
data.혈색소 = data.혈색소.replace(np.nan,-1)
data.요단백 = data.요단백.replace(np.nan,-1)
data.혈청크레아티닌 = data.혈청크레아티닌.replace(np.nan,-1)
data.AST = data.AST.replace(np.nan,-1)
data.ALT = data.ALT.replace(np.nan,-1)
data.감마지티피 = data.감마지티피.replace(np.nan,-1)
data.흡연상태 = data.흡연상태.replace(np.nan,-1)
data.음주여부 = data.음주여부.replace(np.nan,-1)
data.구강검진수검여부 = data.구강검진수검여부.replace(np.nan,-1)




#Train data와 Test data로 나누기 위한 과정,
#가입자 일련번호가 5로 끝날 시 Test Data로
#이외에는 모두 Train Data로 분류

row_idx_train = []
row_idx_test = []
for i in range(1,len(data.가입자일련번호)+1):
    if i%10 != 0 and i%5==0:
        row_idx_train.append(i-1)
    else:
        row_idx_test.append(i - 1)

#Train, Test Data를 Dataset으로부터 구분하는 코드
train_data = data.drop(row_idx_train,0)
test_data = data.drop(row_idx_test,0)


print(train_data)
print(test_data)

#train_data와 test_data를 각각 csv파일로 저장
train_save_path ="C:/Users/whals/Desktop/kakao/train_data.csv"
test_save_path = "C:/Users/whals/Desktop/kakao/test_data.csv"
train_data.to_csv(train_save_path,encoding='cp949')
test_data.to_csv(test_save_path,encoding='cp949')
