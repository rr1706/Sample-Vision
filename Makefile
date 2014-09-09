all:
	g++ -g -std=c++11 sample.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -o sample
