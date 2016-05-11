import numpy as np, cv2, datetime, time
from imutils.video import VideoStream
import imutils
import argparse

#Argument parser to select picamera or USB webcamera
ap=argparse.ArgumentParser()
ap.add_argument("-p", "--picamera", type=int, default=-1,
	help="whether or not the Raspberry Pi camera should be used")
ap.add_argument("-v", "--video", help="path to video file")
ap.add_argument("-b", "--buffer", type=int, default=64, help="max buffer size")
args=vars(ap.parse_args())

camera = VideoStream(usePiCamera=args["picamera"] > 0).start()
time.sleep(2)   #camera start time

while True:
        #Read the frame
        frame = camera.read()        
        #Reshape to 400 pixel width
	frame = imutils.resize(frame, width=400)
        #Display frame        
        cv2.imshow('OrigFrame',frame)

        #Press 'q' to quit
        key=cv2.waitKey(1)& 0xFF
        if key==ord("q"):
               break

#close the imshow window
cv2.destroyAllWindows()
#Stop camera
camera.stop()
