#pragma once
#include "Image.h"
#include <vector>

namespace ImagePrediction
{
	enum Mode
	{
		Left_1, Left_2, Left_3,
		Top_1, Top_2, Top_3,
		Median, Graham, MED_MAP
	};
	Image LeftPrediction(Image image, Mode mode, bool backward = false);
	Image TopPrediction(Image image, Mode mode, bool backward = false);
	Image MedianPrediction(Image image, Mode mode, bool backward = false);

	Image GrahamPrediction(Image image);
	Image GrahamPredictionBack(Image image);

	Image MED_MAP_Prediction(Image image);
	Image MED_MAP_PredictionBack(Image image);

	int MedianValue(std::vector<int>& m);
}

