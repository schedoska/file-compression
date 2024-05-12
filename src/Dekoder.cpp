#include "../include/Decoder.h"
#include "../include/Utils.h"
#include <fstream>

int main(int argc, char * argv[])
{
    if(argc < 2){
        std::cout << "No input or output file.";
        return 0;
    }
    std::string inFileName(argv[1]);
    std::string outFileName(argv[2]);

    std::string predModeStr;
    if(argc > 2) predModeStr = argv[3];
    else predModeStr = "L1";
    ImagePrediction::Mode predMode = StringToMode(predModeStr);

    Decoder decoder;
    Image image = decoder.DecodeImage(inFileName, predMode);
    ImageIO::WriteImage(image, outFileName);
    return 0;
}