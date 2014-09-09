// opencv project inclues
#include <opencv2/core/core.hpp>
// image processing
#include <opencv2/imgproc/imgproc.hpp>
// window management
#include <opencv2/highgui/highgui.hpp>

#include <vector>

const int kern_mat0[] = {1,0,1,
                        0,1,0,
						1,0,1};
cv::Mat kernel0 = getStructuringElement(*kern_mat0, cv::Size(3,3), cv::Point(-1,-1));


int main()
{
	// control access to camera
	// parameter 0 - first camera
	cv::VideoCapture camera(0);
	if (!camera.isOpened())
		return 2;
	// object to store image data
	cv::Mat image, track, doge;
	doge = cv::imread("doge.jpg");
	// object to store key press
	char key;
	cv::namedWindow("Camera image", CV_WINDOW_NORMAL);
	// loop forever (infinite)
	while (1) {
		std::vector<std::vector<cv::Point> > contours;
		std::vector<cv::Vec4i> hierarchy;
		// read image data from the camera and store it in the image object
		camera >> image;
		// 1st param - input
		// 2nd param - output
		// 3rd param - action to apply
		cv::cvtColor(image, track, CV_BGR2HSV);
		cv::inRange(track, cv::Scalar(70, 0, 203), cv::Scalar(129, 20, 255), track);
		cv::morphologyEx(track, track, cv::MORPH_OPEN, kernel0, cv::Point(-1, -1), 2);
		cv::imshow("Test", track);
		cv::findContours(track, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE, cv::Point(0, 0));
		std::vector<std::vector<cv::Point> > polygons(contours.size());
		auto it = contours.begin();
		int i = 0;
		for (; it < contours.end(); ++it, ++i) {
			if (contourArea(*it) < 500)
				continue;
			cv::approxPolyDP(contours[i], polygons[i], 10, true);
			drawContours(image, polygons, i, cv::Scalar(255, 0, 0));
			cv::Rect rect = cv::boundingRect(polygons[i]);
			cv::Mat dog;
			cv::resize(doge, dog, cv::Size(rect.width, rect.height));
			cv::Rect roi(cv::Point(rect.x, rect.y), cv::Size(rect.width, rect.height));
			cv::Mat dest = image(roi);
			dog.copyTo(dest);
		}
		// creates a window called "Camera image" and shows the image in it
		cv::imshow("Camera image", image);
		// waits for keyboard input
		// param 33 - milliseconds to wait for
		// assigns the result to variable key
		key = cv::waitKey(33);
		// if key is Escape then
		if (key == 27)
			// quit the program safely
			break;
	}
	// cleans up the camera
	camera.release();
	return 0;
}

