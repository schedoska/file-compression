#include "../include/Encoder.h"
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

    Image image = ImageIO::ReadImage(inFileName);
    std::cout << "\nImage: \"" << inFileName << "\"\n";
    std::cout << "w: " << image.GetHeight() << ", h: " << image.GetHeight() << "\n";

    std::ifstream in(inFileName, std::ifstream::ate | std::ifstream::binary);
    int orgFileSize = in.tellg();
    std::cout << "File size: " << orgFileSize << " B\n\n";

    Encoder encoder;
    std::cout << "Compression to: \"" << outFileName << "\"\n\n";
    encoder.EncodeImage(image, outFileName, predMode);

    std::unordered_map<int16_t, std::string> dictionary = encoder.GetDictionary();
    for (auto n : dictionary) {
		std::cout << "[ " << n.first << " ] : " << n.second << "\n";
	}

    std::ifstream out(outFileName, std::ifstream::ate | std::ifstream::binary);
    int newFileSize = out.tellg();
    float eff = (float)(newFileSize - orgFileSize) / (float)orgFileSize;
    std::cout << "\nFile size after compression: " << newFileSize << " B  (" << eff * 100.0 << " %)\n\n";
    return 0;
}