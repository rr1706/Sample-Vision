sample OpenCV application
======

By Connor Monahan, Team 1706.

This project is a sample vision program in C++ using the OpenCV library.

The base tag version is a simple camera application that streams images
from the computer's webcam to a window on the screen, to demo how image
capture works using OpenCV.

The tracker version is a simple application doing computer vision tracking
using the steps outlined by Hunter. They are as follows:

* Capture Image
* Threshold
* Erode / Dilate (open)
* Find contours
* Test each contour
* Display results

The example tracker takes the camera input and replaces bright white objects
(intended to track lights) and sprays the specified image overlaying the
detected object.
