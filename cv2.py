#!/usr/bin/env python
# coding: utf-8

# In[1]:


import cv2
import numpy as np
import matplotlib.pyplot as plt


# In[2]:


img = cv2.imread('C:/Users/19378/Pictures/Camera Roll/hmmm.jpg',cv2.IMREAD_GRAYSCALE)

plt.imshow(img, cmap = 'gray', interpolation = 'bicubic')
plt.plot([600,600,600],[0,200,400],'b', linewidth=10) #just to draw on the image 
plt.show()


# cv2.waitKey(0)
# cv2.destroyAllWindows()


# # cutting the image and Region of Image (ROI)

# In[3]:


img = cv2.imread('C:/Users/19378/Pictures/Camera Roll/jsk.jpeg',cv2.IMREAD_COLOR)
px = img[200,200]
img [200,200] = [255,255,255]
print(px)


#USed to select perticular set of pixels (ie 100to700) = white colour 
#img [50:100,500:750] = [255,255,255] #left number should be lesser than right 

cut_img = img[50:100, 500:750]
img [0:50, 0:250] = cut_img


cv2.imshow('me', img)
cv2.waitKey(0)
cv2.destroyAllWindows()


# # Threshold 

# In[4]:


image = cv2.imread('C:/Users/19378/Pictures/Camera Roll/hmmm.jpg')
#retval, threshold = cv2.threshold(image, 12, 250, cv2.THRESH_BINARY)
greyscale = cv2.cvtColor (image, cv2.COLOR_BGR2GRAY)

cv2.imshow('og', image)
cv2.imshow('grey',image)
#cv2.imshow('threshold', threshold)
cv2.waitKey(0)
cv2.destroyALlWindows()


# # video 

# In[ ]:


cap = cv2.VideoCapture(0)
 
while(True):
    ret, frame = cap.read() #color 
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) #grey
 
    cv2.imshow('grey',gray)
    cv2.imshow('color',frame)
    if cv2.waitKey(0) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()


# # Haar 

# In[ ]:





# In[2]:


import numpy as np
import cv2

#face_cascade = cv2.CascadeClassifier('C:/openpose-1.6.0-binaries-win64-only_cpu-python-flir-3d/openpose/models/face/haarcascade_frontalface_alt.xml')
face_cascade = cv2.CascadeClassifier('C:/Users/19378/Desktop/Education/LEARNING/haar_cascade_xml_files/haarcascade_frontalface_default.xml')
#https://github.com/Itseez/opencv/blob/master/data/haarcascades/haarcascade_eye.xml
eye_cascade = cv2.CascadeClassifier('C:/Users/19378/Desktop/Education/LEARNING/haar_cascade_xml_files/haarcascade_eye.xml') 

cap = cv2.VideoCapture(0)

while 1:
    #capture it frame-by-frame
    ret, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5) #scaleFactor, mineNeighbours

    for (x,y,w,h) in faces:
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
        roi_gray = gray[y:y+h, x:x+w] #region of interest
        roi_color = img[y:y+h, x:x+w]
        
#         img_item = "my-image.png"
#         cv2.imrite(img_item, roi_gray) #to save the image of my face
        eyes = eye_cascade.detectMultiScale(roi_gray)
        for (ex,ey,ew,eh) in eyes:
            cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)

    cv2.imshow('img',img)
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cap.release()
cv2.destroyAllWindows()


# # with smile feature

# In[ ]:


import numpy as np
import cv2

face_cascade = cv2.CascadeClassifier('C:/Users/19378/Desktop/haarcascade_frontalface_default.xml')
#https://github.com/Itseez/opencv/blob/master/data/haarcascades/haarcascade_eye.xml
eye_cascade = cv2.CascadeClassifier('C:/Users/19378/Desktop/haarcascade_eye.xml')

smilee = cv2.CascadeClassifier('C:/Users/19378/Desktop/haarcascade_smile.xml')

cap = cv2.VideoCapture(0)

while 1:
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    red = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 2)

    for (x,y,w,h) in faces:
        cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),2)
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = frame[y:y+h, x:x+w]
        roi_red = red[y:y+h, x:x+w]
        
        eyes = eye_cascade.detectMultiScale(roi_gray)
        smile = smilee.detectMultiScale(roi_red)
        for (ex,ey,ew,eh) in eyes:
            cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)
            
        for (sx,sy,sw,sh) in smile:
            cv2.rectangle(roi_color,(sx,sy),(sx+sw,sy+sh),(0,0,255),2)

    cv2.imshow('frame',frame)
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cap.release()
cv2.destroyAllWindows()

