#pragma once
#include "Huffman.h"
#include "ImagePrediction.h"

class Encoder
{
	class BitWriter
	{
	public:
		BitWriter();
		void Write(bool bit, std::ofstream& file);
		void Write(char bit, std::ofstream& file);
		void Write(std::string bitArray, std::ofstream& file);
		void Write(std::int16_t value, std::ofstream& file);
		void Dump(std::ofstream& file);

	private:
		char buffor;
		int count;
	};

public:
	Encoder();
	~Encoder();
	void EncodeImage(Image image, std::string fileName, ImagePrediction::Mode mode);
	std::unordered_map<int16_t, std::string> GetDictionary();
	Huffman::Node* GetTreeRoot();
	void SetHistogramFile(bool generateFile);

private:
	Huffman::Node* root;
	std::unordered_map<int16_t, std::string> dictionary;

	void EncodeNode(Huffman::Node* node, BitWriter& bitWriter, std::ofstream& file);
	Image GeneratePredictionImage(Image image, ImagePrediction::Mode mode);

	bool generateHistogram;
};






