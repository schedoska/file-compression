#pragma once
#include "Image.h"
#include "matrix.h"
#include <vector>

namespace ImagePrediction
{
	enum Mode
	{
		Left_1, Left_2, Left_3,
		Top_1, Top_2, Top_3,
		Median, Graham, MED_MAP,
		LPC_2, LPC_3, LPC_4, LPC_5,
		LPC_7, LPC_10
	};

	Image Left_Prediction(Image image, Mode mode);
	Image Left_PredictionBack(Image image, Mode mode);
	Image Top_Prediction(Image image, Mode mode);
	Image Top_PredictionBack(Image image, Mode mode);

	Image MedianPrediction(Image image, Mode mode, bool backward = false);

	Image GrahamPrediction(Image image);
	Image GrahamPredictionBack(Image image);

	Image MED_MAP_Prediction(Image image);
	Image MED_MAP_PredictionBack(Image image);
	int MedianValue(std::vector<int>& m);

	struct LpcData
	{
		LpcData(Image image = Image(1,1), int contextSize = 0, Matrix<float> param = Matrix<float>(1));
		Image image;
		int contextSize;
		Matrix<float> param;
	};

	LpcData LpcPrediction(Image image, int contextSize);
	Image LpcPredictionBack(LpcData LpcImage);
	float xcorr(Image &image, int k);
}

