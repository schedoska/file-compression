#include <string>
#include "ImagePrediction.h"

ImagePrediction::Mode StringToMode(std::string modestr);
uint8_t ModeByteCode(ImagePrediction::Mode mode);
int ModeToContextSize(ImagePrediction::Mode mode);
