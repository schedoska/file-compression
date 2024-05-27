#include "../include/ImagePrediction.h"
#include "../include/matrix.h"
#include <algorithm>
#include <iostream>

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

Image ImagePrediction::GrahamPrediction(Image image)
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
			int16_t pred = (image(x-1,y-1)-image(x,y-1)) > abs(image(x-1,y-1)-image(x-1,y)) ?
				image(x,y-1) : image(x-1,y);
			imageB(x,y) = image(x,y) - pred;
		}
	}
	return imageB;
}

Image ImagePrediction::GrahamPredictionBack(Image image)
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
			int16_t pred = (imageB(x-1,y-1)-imageB(x,y-1)) > abs(imageB(x-1,y-1)-imageB(x-1,y)) ?
				imageB(x,y-1) : imageB(x-1,y);
			imageB(x,y) = pred + image(x,y);
		}
	}
	return imageB;
}

Image ImagePrediction::MED_MAP_Prediction(Image image)
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
			int16_t pred;
			if(image(x-1,y-1) >= std::max(image(x-1,y),image(x,y-1))) 
				pred = std::min(image(x-1,y),image(x,y-1));
			else if(image(x-1,y-1) <= std::min(image(x-1,y),image(x,y-1)))
				pred = std::max(image(x-1,y),image(x,y-1));
			else
				pred = image(x,y-1) + image(x-1,y) - image(x-1,y-1);
			imageB(x,y) = image(x,y) - pred;
		}
	}
	return imageB;
}

Image ImagePrediction::MED_MAP_PredictionBack(Image image)
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
			int16_t pred;
			if(imageB(x-1,y-1) >= std::max(imageB(x-1,y),imageB(x,y-1))) 
				pred = std::min(imageB(x-1,y),imageB(x,y-1));
			else if(imageB(x-1,y-1) <= std::min(imageB(x-1,y),imageB(x,y-1)))
				pred = std::max(imageB(x-1,y),imageB(x,y-1));
			else
				pred = imageB(x,y-1) + imageB(x-1,y) - imageB(x-1,y-1);
			imageB(x,y) = pred + image(x,y);
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

ImagePrediction::LpcData::LpcData(Image image_, int contextSize_, Matrix<float> param_)
{
	image = image_;
	contextSize = contextSize_;
	param = param_;
}

ImagePrediction::LpcData ImagePrediction::LpcPrediction(Image image, int contextSize)
{
	int h = image.GetHeight();
	int w = image.GetWidth();
	ImagePrediction::LpcData imageLpc;
	imageLpc.image = Image(w, h);
	imageLpc.contextSize = contextSize;

	Matrix<float> R(contextSize, contextSize);
	Matrix<float> r(contextSize, 1);

	for (int i = 0; i < imageLpc.contextSize; i++) {
		for (int q = 0; q < imageLpc.contextSize; q++) {
			if (q <= i) R.at(i,q) = xcorr(image, (i-q));
			else R.at(i,q) = xcorr(image, (q-i));
		}
	}
	for(int i = 0; i < contextSize; i++){
		r.at(i,0) = xcorr(image, i+1);
	} 
	imageLpc.param = R.inv() * r;
	
	std::cout << "LPC optmial parameters:\n";
	for(int q = 0; q < contextSize; ++q)
		std::cout << "[a" << q+1 << ": " <<imageLpc.param.at(q,0) << "], ";
	std::cout << "\n\n";
	
	for (int x = 0; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
			double pred = 0;
			for(int k = 0; k < contextSize; k++) 
				pred += imageLpc.param.at(k,0) * image.Value(x-(k+1), y);
			imageLpc.image(x,y) = image(x,y) - (int)pred;
		}
	}
	
	return imageLpc;
}

Image ImagePrediction::LpcPredictionBack(LpcData LpcImage)
{
	Image image = LpcImage.image;
	Matrix<float> param = LpcImage.param;
	int contextSize = LpcImage.contextSize;

	int h = image.GetHeight();
	int w = image.GetWidth();
	Image imageB(w, h);

	for (int y = 0; y < w; ++y) {
		imageB(0, y) = image(0, y);
	}
	for (int x = 1; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
			double pred = 0;
			for(int k = 0; k < contextSize; k++) 
				pred += param.at(k,0) * imageB.Value(x-(k+1), y);
			imageB(x,y) = (int)pred + image(x,y);
		}
	}
	return imageB;
}

float ImagePrediction::xcorr(Image &image, int k)
{
	int h = image.GetHeight();
	int w = image.GetWidth();
	double cor = 0;
	for (int x = 0; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
				cor += image.Value(x-k, y) * image.Value(x, y);
		}
	}
	return (double)cor / (double)(h*w);
}
