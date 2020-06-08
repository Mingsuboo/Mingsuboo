import cv2
import matplotlib.pyplot as plt
read_path = "./DATA/styleEleganceActive/styleEleganceActive_negative/img"
save_path = "./DATA/styleEleganceActive/styleEleganceActive_negative/black"
for i in range(1,5833): #positive:5891,negative:5833, zero:837
    그림BGR = cv2.imread(read_path+str(i)+'.jpg')
    #그림RGB = cv2.cvtColor(그림BGR, cv2.COLOR_BGR2RGB)
    #그림좌우반전 = cv2.flip(그림RGB, 1)

    그림RGB = cv2.cvtColor(그림BGR, cv2.COLOR_BGR2RGB)
    그림흑백 = cv2.cvtColor(그림BGR, cv2.COLOR_BGR2GRAY)




    # 이 아래 부분은 그림을 화면에 출력하기 위한 부분으로, OpenCV 알고리즘과는 상관이 없습니다.
    #plt.subplot(1, 2, 1)  # 1행 2열에서 1번째 열
    #plt.imshow(그림RGB)
    #plt.xticks([])  # x축 좌표 숨김
    #plt.yticks([])  # y축 좌표 숨김

    #plt.subplot(1, 2, 2)  # 1행 2열에서 2번째 열
    #plt.imshow(그림흑백, cmap='gray')
    #plt.xticks([])  # x축 좌표 숨김
    #plt.yticks([])  # y축 좌표 숨김
    #plt.show()
    #그림좌우반전 = cv2.cvtColor(그림좌우반전, cv2.COLOR_RGB2BGR)
    cv2.imwrite(save_path+str(i)+'.jpg', 그림흑백)

