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

    Decoder decoder;
    Image image = decoder.DecodeImage(inFileName);
    ImageIO::WriteImage(image, outFileName);

    image.printImageData();
    return 0;
}