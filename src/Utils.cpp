#include "../include/Utils.h"

ImagePrediction::Mode StringToMode(std::string modestr)
{
    if(modestr == "L1") return ImagePrediction::Mode::Left_1;
    else if(modestr == "L2") return ImagePrediction::Mode::Left_2;
    else if(modestr == "L3") return ImagePrediction::Mode::Left_3;

    if(modestr == "T1") return ImagePrediction::Mode::Top_1;
    else if(modestr == "T2") return ImagePrediction::Mode::Top_2;
    else if(modestr == "T3") return ImagePrediction::Mode::Top_3;

    if(modestr == "M") return ImagePrediction::Mode::Median;
    else if(modestr == "G") return ImagePrediction::Mode::Graham;
    else if(modestr == "MED") return ImagePrediction::Mode::MED_MAP;

    return ImagePrediction::Mode::Left_1;
}