#include "../include/Encoder.h"
#include <fstream>

Encoder::Encoder()
{
	root = nullptr;
}

Encoder::~Encoder()
{
	DeleteTree(root);
}

void Encoder::EncodeImage(Image image, std::string fileName, ImagePrediction::Mode mode)
{
	image = GeneratePredictionImage(image, mode);

	DeleteTree(root);
	dictionary.clear();

	root = Huffman::GenerateTree(image);
	GenerateDictionary(dictionary, root, "");

	std::ofstream file(fileName, std::ios::binary);
	int16_t h = image.GetHeight();
	int16_t w = image.GetWidth();
	file.write((char*)&w, 2);
	file.write((char*)&h, 2);

	char m = (char)mode;
	file.write(&m, 1);	//Informacja o trybie predykcji

	BitWriter bitWriter;
	EncodeNode(root, bitWriter, file);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			std::string token = dictionary[image(x, y)];
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
