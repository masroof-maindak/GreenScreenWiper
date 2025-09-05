#include <opencv2/core/types.hpp>
#include <print>

#include <opencv2/core.hpp>
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

/*
 * Since string_view doesn't work for the likes of namedWindow & showImage, and
 * the small-string optimisation probably applies anyway.
 */
constexpr std::string INPUT_WINNAME{"Input"};
constexpr std::string OUTPUT_WINNAME{"Output"};
constexpr std::string OUTPUT_FNAME{"processed.png"};

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::println(stderr, "Usage: {} <input-img-path>", argv[0]);
		return 1;
	}

	cv::Mat fg_img{cv::imread(argv[1], cv::IMREAD_COLOR_BGR)};
	if (fg_img.data == nullptr) {
		std::println(stderr, "Failed to read/parse foreground. Exiting");
		return 2;
	}

	// TODO: get from argument
	cv::Mat bg_img{cv::imread("../bg.jpg", cv::IMREAD_COLOR_BGR)};
	if (fg_img.data == nullptr) {
		std::println(stderr, "Failed to read/parse background. Exiting");
		return 3;
	}

	// Convert images to HSV
	cv::Mat hsv_fg{};
	cv::cvtColor(fg_img, hsv_fg, cv::COLOR_BGR2HSV);

	cv::Mat hsv_bg{};
	cv::cvtColor(fg_img, hsv_bg, cv::COLOR_BGR2HSV);

	// Generate mask for green colours in HSV
	cv::Mat mask{};
	cv::Scalar lowerb{36, 0, 0};
	cv::Scalar upperb{86, 255, 255};
	cv::inRange(hsv_fg, lowerb, upperb, mask);

	// Merge two images
	cv::Mat extracted{};
	// FIXME
	cv::bitwise_and(hsv_fg, hsv_bg, extracted, mask);
	cv::copyTo(hsv_fg, hsv_bg, mask);

	cv::namedWindow(INPUT_WINNAME, cv::WINDOW_AUTOSIZE);
	cv::namedWindow(OUTPUT_WINNAME, cv::WINDOW_FREERATIO);

	cv::imshow(INPUT_WINNAME, fg_img);
	cv::imshow(OUTPUT_WINNAME, hsv_fg);
	cv::waitKey(0);

	cv::imwrite("plesae.jpg", hsv_bg);
	cv::imwrite("plesae2.jpg", extracted);

	cv::destroyAllWindows();
	return 0;
}
