#include <print>
#include <string_view>

#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

constexpr std::string_view OUTPUT_FNAME{"../processed.png"};

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::println(stderr, "Usage: {} <path>", argv[0]);
		return 1;
	}

	cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);
	if (img.data == nullptr) {
		std::println(stderr, "Failed to read/parse image. Exiting");
		return 2;
	}

	cv::namedWindow("Input", cv::WINDOW_FREERATIO);
	// cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);

	cv::imshow("Input", img);

	cv::waitKey(0);

	cv::destroyAllWindows();
	return 0;
}
