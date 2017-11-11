# from PIL import Image, ImageDraw
import face_recognition
import numpy as np
import math
import time
import cv2
import socket_lib

# S = socket_lib.ClientSocket()

video_capture = cv2.VideoCapture(0)

face_locations = []
face_names = []
process_this_frame = 0
oc_time = 0
oc_debounced = False
nom = False

up_mark = None
down_mark = None

while True:
    ret, frame = video_capture.read()
    small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)

    face_locations = face_recognition.face_locations(small_frame, 1)
    face_landmarks = face_recognition.face_landmarks(small_frame, face_locations)
    for face in face_landmarks:
        for feature in face:
            cv2.polylines(frame, np.array([face[feature]])*4, isClosed=False, color=(255,0,0), thickness=4)

    face_mean_x = []
    face_mean_y = []
    for face in face_landmarks:
        for feature in ['right_eye', 'left_eye']:
            for (x, y) in face[feature]:
                face_mean_x.append(x)
                face_mean_y.append(y)

    if face_mean_x:
        face_sd = np.std(face_mean_x) + np.std(face_mean_y)
        face_x = sum(face_mean_x)/len(face_mean_x)
        face_y = sum(face_mean_y)/len(face_mean_y)

        nose_x = face_landmarks[0]['nose_bridge'][-1][0]
        nose_y = face_landmarks[0]['nose_bridge'][-1][1]

        top_lip_x = face_landmarks[0]['top_lip'][-3][0]
        top_lip_y = face_landmarks[0]['top_lip'][-3][1]

        bot_lip_x = face_landmarks[0]['bottom_lip'][-3][0]
        bot_lip_y = face_landmarks[0]['bottom_lip'][-3][1]


        jaw_tips_x = (face_landmarks[0]['chin'][0][0] + face_landmarks[0]['chin'][-1][0])/2
        jaw_tips_y = (face_landmarks[0]['chin'][0][1] + face_landmarks[0]['chin'][-1][1])/2

        lr_metric = (nose_x - face_x)/face_sd
        lr = "center"
        if lr_metric > 0.3:
            lr = "left"
        if lr_metric < -0.3:
            lr = "right"

        ud_metric = (nose_y - face_y)/face_sd
        ud = 'center'
        if up_mark and down_mark:
            # print("ha", up_mark, down_mark)
            if ud_metric < up_mark + (down_mark - up_mark) * 0.3:
                ud = "up"
            if ud_metric > down_mark + (up_mark - down_mark) * 0.15:
                ud = "down"
        else:
            if ud_metric < 0.3:
                ud = "up"
            if ud_metric > 1.0:
                ud = "down"


        oc_metric = math.sqrt((top_lip_x - bot_lip_x)**2 + (top_lip_y - bot_lip_y)**2)/face_sd
        oc = 'closed'
        if oc_metric >= 0.2:
            oc = 'open'

            # print("closed")
            # print(d)
        # print(face_sd)

        if oc != oc_debounced:
            if time.clock() - oc_time > 0.05:
                oc_debounced = oc;
                oc_time = time.clock()
        else:
            oc_time = time.clock()

        if oc_debounced == 'closed':
            if not nom:
                if lr == "left":
                    print("left"+ ' '*50)
                    # S.sendLeft()
                elif lr == "right":
                    print("right"+ ' '*50)
                    # S.sendRight()
                elif ud == "up":
                    print("up" + ' '*50)
                    # S.sendUp()
                elif ud == "down":
                    print("down"+ ' '*50)
                    # S.sendDown()
            nom = True
        else:
            nom = False

            
        cv2.circle(frame, (nose_x*4, nose_y*4), 10, color=(0,0,255), thickness=4)
        cv2.circle(frame, (top_lip_x*4, top_lip_y*4), 10, color=(0,0,255), thickness=4)
        cv2.circle(frame, (bot_lip_x*4, bot_lip_y*4), 10, color=(0,0,255), thickness=4)

        print(lr.ljust(7),
              ud.ljust(7),
              oc_debounced.ljust(7),
              "{0: >6.3f}".format(lr_metric),
              "{0: >6.3f}".format(ud_metric),
              "{0: >6.3f}".format(oc_metric),
              end="\r")

    # Display the resulting image
    cv2.imshow('Video', frame)

    # Hit 'q' on the keyboard to quit!
    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        break
    elif key == ord('u'):
        up_mark = ud_metric
    elif key == ord('d'):
        down_mark = ud_metric

# Release handle to the webcam
# del S
video_capture.release()
cv2.destroyAllWindows()
