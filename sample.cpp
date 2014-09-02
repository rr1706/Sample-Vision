// opencv project inclues
#include <opencv2/core/core.hpp>
// image processing
#include <opencv2/imgproc/imgproc.hpp>
// window management
#include <opencv2/highgui/highgui.hpp>

int main()
{
	// control access to camera
	// parameter 0 - first camera
	cv::VideoCapture camera(0);
	// object to store image data
	cv::Mat image;
	// object to store key press
	char key;
	// loop forever (infinite)
	while (1) {
		// read image data from the camera and store it in the image object
		camera >> image;
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

