#include "../include/Encoder.h"
#include "../include/Utils.h"
#include <fstream>

Encoder::Encoder()
{
	root = nullptr;
	SetHistogramFile(false);
}

Encoder::~Encoder()
{
	DeleteTree(root);
}

void Encoder::SetHistogramFile(bool generateFile)
{
	generateHistogram = generateFile;
}

void Encoder::EncodeImage(Image image, std::string fileName, ImagePrediction::Mode mode)
{
	Image image2;
	ImagePrediction::LpcData imageLpc;
	imageLpc.contextSize = ModeToContextSize(mode);

	if (imageLpc.contextSize) {
		imageLpc = ImagePrediction::LpcPrediction(image, imageLpc.contextSize);
		image2 = imageLpc.image;
	}
	else {
		image2 = GeneratePredictionImage(image, mode);
	}
	
	std::cout << "Entropy value: " << image.EntropyValue() << "\n";
	std::cout << "Entropy value after prediction: " << image2.EntropyValue() << "\n";
	if(generateHistogram){
		std::cout << "Generating \"Histogram.dat\" and \"Histogram_pred.dat\" files\n";
		ImageIO::WriteHistogramData(image.HistogramData(), "image.hist");
		ImageIO::WriteHistogramData(image2.HistogramData(), "image_prediction.hist");
	}
	DeleteTree(root);
	dictionary.clear();

	root = Huffman::GenerateTree(image2);
	GenerateDictionary(dictionary, root, "");
	std::cout << "Mean bit length after encoding: " << Huffman::MeanBitSize(dictionary, image2) << "\n\n";

	std::ofstream file(fileName, std::ios::binary);
	int16_t h = image2.GetHeight();
	int16_t w = image2.GetWidth();
	file.write((char*)&w, 2);
	file.write((char*)&h, 2);

	char m = (char)mode;
	file.write(&m, 1);	//Informacja o trybie predykcji
	
	if (imageLpc.contextSize){
		for(int k = 0; k < imageLpc.contextSize; k++){
			file.write((char*)&imageLpc.param.at(k,0), sizeof(float));
		}
	}

	BitWriter bitWriter;
	EncodeNode(root, bitWriter, file);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			std::string token = dictionary[image2(x, y)];
			bitWriter.Write(token, file);
		}
	}
	bitWriter.Dump(file);

	file.close();
	return;
}

std::unordered_map<int16_t, std::string> Encoder::GetDictionary()
{
	return dictionary;
}

Huffman::Node* Encoder::GetTreeRoot()
{
	return root;
}

void Encoder::EncodeNode(Huffman::Node* node, BitWriter& bitWriter, std::ofstream& file)
{
	if (node->isLeaf) {
		bitWriter.Write(true, file);
		bitWriter.Write((int16_t)node->value, file);
	}
	else {
		bitWriter.Write(false, file);
		EncodeNode(node->left, bitWriter, file);
		EncodeNode(node->right, bitWriter, file);
	}
}

Image Encoder::GeneratePredictionImage(Image image, ImagePrediction::Mode mode)
{
	switch(mode) {
	case ImagePrediction::Mode::Left_1:
	case ImagePrediction::Mode::Left_2:
	case ImagePrediction::Mode::Left_3:
		return ImagePrediction::LeftPrediction(image, mode);
	case ImagePrediction::Mode::Top_1:
	case ImagePrediction::Mode::Top_2:
	case ImagePrediction::Mode::Top_3:
		return ImagePrediction::TopPrediction(image, mode);
	case ImagePrediction::Mode::Median:
		return ImagePrediction::MedianPrediction(image, mode);
	case ImagePrediction::Mode::Graham:
		return ImagePrediction::GrahamPrediction(image);
	case ImagePrediction::Mode::MED_MAP:
		return ImagePrediction::MED_MAP_Prediction(image);
	default:
		return image;
	}
}


Encoder::BitWriter::BitWriter()
{
	buffor = 0;
	count = 0;
}

void Encoder::BitWriter::Write(bool bit, std::ofstream& file)
{
	if (bit) buffor |= 1;
	count++;
	if (count == 8) {
		file.write(&buffor, sizeof(buffor));
		count = 0;
		buffor = 0;
	}
	else {
		buffor <<= 1;
	}
}

void Encoder::BitWriter::Write(char bit, std::ofstream& file)
{
	if (bit == '1') buffor |= 1;
	count++;
	if (count == 8) {
		file.write(&buffor, sizeof(buffor));
		count = 0;
		buffor = 0;
	}
	else {
		buffor <<= 1;
	}
}

void Encoder::BitWriter::Write(std::string bitArray, std::ofstream& file)
{
	while (!bitArray.empty()) {
		Write(bitArray[0], file);
		bitArray.erase(0, 1);
	}
}

void Encoder::BitWriter::Write(std::int16_t value, std::ofstream& file)
{
	for (int i = 0; i < sizeof(value) * 8; i++) {
		Write((bool)(value & 0x8000), file);
		value <<= 1;
	}
}

void Encoder::BitWriter::Dump(std::ofstream& file)
{
	if (count > 0){
		buffor <<= (7 - count);
		file.write(&buffor, sizeof(buffor));
	}
}
