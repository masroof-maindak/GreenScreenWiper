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

constexpr int LAB_A_CHAN_IDX{1};

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::println(stderr, "Usage: {} <path>", argv[0]);
		return 1;
	}

	cv::Mat img{cv::imread(argv[1], cv::IMREAD_COLOR_BGR)};
	if (img.data == nullptr) {
		std::println(stderr, "Failed to read/parse image. Exiting");
		return 2;
	}

	// Convert image to lab
	cv::Mat lab_img{};
	cv::cvtColor(img, lab_img, cv::COLOR_BGR2Lab);

	// Extract green-red channel
	cv::Mat_<cv::Vec<uchar, 1>> a_channel{};
	cv::extractChannel(lab_img, a_channel, LAB_A_CHAN_IDX);

	int count{};
	for (const auto &pxl : a_channel) {
		// FIXME: doesn't work.
		// if (pxl(0) < 0)
		// 	count++;

		count++;
	}

	std::println("Count: {}", count);

	// cv::namedWindow(INPUT_WINNAME, cv::WINDOW_FREERATIO);
	// cv::namedWindow(OUTPUT_WINNAME, cv::WINDOW_FREERATIO);

	// cv::imshow(INPUT_WINNAME, img);
	// cv::imshow(OUTPUT_WINNAME, a_channel);
	// cv::waitKey(0);

	// cv::destroyAllWindows();
	return 0;
}
