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
	cv::Mat_<uchar> a_channel{};
	cv::extractChannel(lab_img, a_channel, LAB_A_CHAN_IDX);
	int count{};

	for (uchar &pixel : a_channel) {
		/*
		 * 'Normalize' pixel:
		 * We're dealing with uchars and values in CIELAB's a* channel are
		 * represented via -128 to 127
		 */
		pixel = 255 - pixel;

		if (pixel < 128)
			count++;
	}

	// TODO: Merge back or some shit, I don't know.

	std::println("Count: {}", count);

	cv::namedWindow(INPUT_WINNAME, cv::WINDOW_FREERATIO);
	cv::namedWindow(OUTPUT_WINNAME, cv::WINDOW_FREERATIO);

	cv::imshow(INPUT_WINNAME, img);
	cv::imshow(OUTPUT_WINNAME, a_channel);
	cv::waitKey(0);

	cv::destroyAllWindows();
	return 0;
}
