#include <print>

#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
	if (argc != 4) {
		std::println(stderr,
					 "Usage: {} <input-img-path> <background-img-path> "
					 "<output-img-path>",
					 argv[0]);
		return 1;
	}

	// Load images
	cv::Mat fg_img{cv::imread(argv[1], cv::IMREAD_COLOR_BGR)};
	if (fg_img.data == nullptr) {
		std::println(stderr, "Failed to read/parse foreground. Exiting");
		return 2;
	}

	cv::Mat bg_img{cv::imread(argv[2], cv::IMREAD_COLOR_BGR)};
	if (fg_img.data == nullptr) {
		std::println(stderr, "Failed to read/parse background. Exiting");
		return 3;
	}

	// Resize background to match foreground (if needed)
	if (fg_img.size() != bg_img.size())
		cv::resize(bg_img, bg_img, fg_img.size());

	// Convert images to HSV
	cv::Mat fg_hsv{};
	cv::cvtColor(fg_img, fg_hsv, cv::COLOR_BGR2HSV);

	cv::Mat bg_hsv{};
	cv::cvtColor(bg_img, bg_hsv, cv::COLOR_BGR2HSV);

	// Generate mask for green colours in HSV
	cv::Mat mask{};
	cv::Scalar lowerb{36, 0, 0};
	cv::Scalar upperb{86, 255, 255};
	cv::inRange(fg_hsv, lowerb, upperb, mask);

	// Create inverse of mask and use it to keep the fg subject
	cv::Mat mask_inv{};
	cv::bitwise_not(mask, mask_inv);
	fg_hsv.copyTo(bg_hsv, mask_inv);

	// Convert back to BGR to save
	cv::Mat result{};
	cv::cvtColor(bg_hsv, result, cv::COLOR_HSV2BGR);
	cv::imwrite(argv[3], result);

	return 0;
}
