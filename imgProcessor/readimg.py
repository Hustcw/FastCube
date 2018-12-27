import cv2  
import numpy
import os
cap = cv2.VideoCapture(0)
# the rectangle startpoint and endpoint
startPoint = (460, 160)
endPoint = (700,400)
# the standard color 
ColorDict = dict([
    ('O', [212,118,55]),
    ('W', [234,221,210]),
    ('R', [190,70,67]),
    ('G', [10,125,72]),
    ('Y', [200,185,55]),
    ('B', [8,25,142])
])



# the record point listt
recordPoint = [
    (x,y) for y in range(startPoint[1],endPoint[1],40)[1::2] for x in range(startPoint[0],endPoint[0],40)[5::-2] 
]

print recordPoint

# return the char 
def getOneColor(r,g,b):
    tempList = []
    for color in ColorDict:
        rgbItem = ColorDict[color]
        tempList.append(((r-rgbItem[0])**2+(g-rgbItem[1])**2+(b-rgbItem[2])**2,color))

    tempList.sort(key = lambda x: x[0])
    print r,g,b
    # print tempList  
    return tempList[0][1]


## write ans to the CUBE_STATE
def getColors(img, flag=1, ):
    ans = []
    for p in recordPoint:
        x=p[0]
        y=p[1]
        ans.append(getOneColor(img[y][x][2],img[y][x][1],img[y][x][0]))

    fp = open("./CUBE_STATE.txt","a+")
    for x in (0,1,2):
        line = ''.join(ans[3*x:3*x + 3])
        print line
        print '\n'
        fp.write(line+'\n')
    print '\n'
    fp.write('\n')
    fp.close()

count = 0
flag = 1
while(1):
    # send py
    if(count == 6):
        print 'yes'
        os.system("python3 sender.py")
        count = 0
        

    # get a frame
    ret, frame = cap.read()
    # show a frame
    Img = cv2.flip(frame,1,dst=None)
    cv2.rectangle(Img, startPoint, endPoint, (0,255,0), 4)
    cv2.imshow("capture", Img)
    judge = cv2.waitKey(1) & 0xFF
    if judge == ord('q'):
        break
    elif judge == ord('p'):
        getColors(Img)
        count +=1
    elif judge == ord('n'):
        fp = open('./CUBE_STATE.txt', 'w')
        fp.close()
    elif judge == ord('u'):
        if count == 0:
            continue
        fp = open('./CUBE_STATE.txt','a+')
        fp.seek(-13,1)
        fp.truncate()
        fp.close()
        count -=1

cap.release()
cv2.destroyAllWindows() 

