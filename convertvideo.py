import cv2
import os 
filename = "v5"
os.mkdir(filename)
vidcap = cv2.VideoCapture(filename+".mp4")
success,image = vidcap.read()
count = 0
while success:
  cv2.imwrite(filename+"/frame%d.png" % count, image)     # save frame as JPEG file      
  success,image = vidcap.read()
  print('Read a new frame: ', count)
  count += 1