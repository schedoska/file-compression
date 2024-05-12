#pragma once
#include "Huffman.h"
#include "ImagePrediction.h"
#include <fstream>

class Decoder
{
	class HuffmanDecoder
	{
	public:
		HuffmanDecoder(Huffman::Node* root_);
		bool PushBit(bool bit, int16_t& val);
		void Restart();

	private:
		Huffman::Node* root;
		Huffman::Node* current_node;
	};

	class BitReader
	{
	public:
		BitReader();
		bool Read(bool &bit, std::ifstream &file);
		bool Read(int16_t& val, std::ifstream& file);

	private:
		char buffor;
		int count;
	};

public:
	Decoder();
	~Decoder();
	Image DecodeImage(std::string fileName, ImagePrediction::Mode mode);

private:
	Huffman::Node* root;
	bool PushToImage(Image& image, int16_t value, int pos);

	int16_t leafCount;
	Huffman::Node* DecodeNode(BitReader& bitReader, std::ifstream& file);
	Image RebuildFromPrediction(Image image, ImagePrediction::Mode mode);
};

