#include "../include/ImagePrediction.h"
#include <algorithm>

Image ImagePrediction::LeftPrediction(Image image, Mode mode, bool backward)
{
	int range;
	if (mode == Mode::Left_1) range = 1;
	else if (mode == Mode::Left_2) range = 2;
	else range = 3;

	int h = image.GetHeight();
	int w = image.GetWidth();
	Image imageB(w,h);

	for (int y = 0; y < h; ++y) {
		imageB(0, y) = image(0, y);
	}
	for (int x = 1; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
			int avg = 0;
			int avgB = 0;
			for (int r = 1; r < range + 1; r++) {
				avg += image(std::max(0, x - r), y);
				avgB += imageB(std::max(0, x - r), y);
			}
			avg /= range;
			avgB /= range;
			backward ? imageB(x, y) = image(x, y) + avgB : imageB(x, y) = image(x, y) - avg;
		}
	}
	return imageB;
}

Image ImagePrediction::TopPrediction(Image image, Mode mode, bool backward)
{
	int range;
	if (mode == Mode::Top_1) range = 1;
	else if (mode == Mode::Top_2) range = 2;
	else range = 3;

	int h = image.GetHeight();
	int w = image.GetWidth();
	Image imageB(w, h);

	for (int x = 0; x < w; ++x) {
		imageB(x, 0) = image(x, 0);
	}
	for (int x = 0; x < w; ++x) {
		for (int y = 1; y < h; ++y) {
			int avg = 0;
			int avgB = 0;
			for (int r = 1; r < range + 1; r++) {
				avg += image(x, std::max(0, y - r));
				avgB += imageB(x, std::max(0, y - r));
			}
			avg /= range;
			avgB /= range;
			imageB(x, y) = (backward ? image(x, y) + avgB : image(x, y) - avg);
		}
	}
	return imageB;
}

Image ImagePrediction::MedianPrediction(Image image, Mode mode, bool backward)
{
	int h = image.GetHeight();
	int w = image.GetWidth();
	Image imageB(w, h);

	for (int x = 0; x < w; ++x) {
		imageB(x, 0) = image(x, 0);
	}
	for (int y = 0; y < w; ++y) {
		imageB(0, y) = image(0, y);
	}

	for (int x = 1; x < w; ++x) {
		for (int y = 1; y < h; ++y) {
			std::vector<int> m;
			if (!backward) {
				m.push_back(image(x - 1, y));
				m.push_back(image(x, y - 1));
				m.push_back(image(x - 1, y - 1));
				imageB(x, y) = image(x, y) - MedianValue(m);
			}
			else {
				m.push_back(imageB(x - 1, y));
				m.push_back(imageB(x, y - 1));
				m.push_back(imageB(x - 1, y - 1));
				imageB(x, y) = image(x, y) + MedianValue(m);
			}
		}
	}
	return imageB;
}

int ImagePrediction::MedianValue(std::vector<int>& m)
{
	if (m.empty()) {
		return 0.0;
	}
	auto n = m.size() / 2;
	std::nth_element(m.begin(), m.begin() + n, m.end());
	auto med = m[n];
	if (!(m.size() % 2)) {
		auto max_it = std::max_element(m.begin(), m.begin() + n);
		med = (*max_it + med) / 2.0;
	}
	return med;
}



