# Object-Tracking-Using-Color-Recognition
object tracking using color recognition
I used OpenCV library with C++ to make this object tracking project using color recognition as it convert camera frame to HSV
image and then we can adjust the ranges of the HSV that will be thresholded then we get moments of image and then we save it to
draw line from the previous place to the current one
#Thresholdng
I made trackbars so i can control the HSV range to be thresholded </br>
thresholding is to convert the image to binary image by making pixels of the specified range black and others white so we can easiy then detect colors
#Moments of image
This calculates the ones in the binary image and so we get the ones in the X axis and ones in Y axis then we get the area of the
ones which then we can get the center of the ones area

</br>
#Sample Video
[![15604873_341482729567703_756784361520496640_n.gif](https://s29.postimg.org/x2wyd9kdj/15604873_341482729567703_756784361520496640_n.gif)](https://postimg.org/image/j98lo7rs3/)
