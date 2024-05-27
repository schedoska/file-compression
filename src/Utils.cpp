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

    if(modestr == "LPC2") return ImagePrediction::Mode::LPC_2;
    else if(modestr == "LPC3") return ImagePrediction::Mode::LPC_3;
    else if(modestr == "LPC4") return ImagePrediction::Mode::LPC_4;
    else if(modestr == "LPC5") return ImagePrediction::Mode::LPC_5;
    else if(modestr == "LPC7") return ImagePrediction::Mode::LPC_7;
    else if(modestr == "LPC10") return ImagePrediction::Mode::LPC_10;

    return ImagePrediction::Mode::Left_1;
}

int ModeToContextSize(ImagePrediction::Mode mode)
{
    switch(mode)
    {
        case ImagePrediction::Mode::LPC_2:
            return 2;
        case ImagePrediction::Mode::LPC_3:
            return 3;
        case ImagePrediction::Mode::LPC_4:
            return 4;
        case ImagePrediction::Mode::LPC_5:
            return 5;
        case ImagePrediction::Mode::LPC_7:
            return 7;
        case ImagePrediction::Mode::LPC_10:
            return 10;
        default:
            return 0;
    }
}
