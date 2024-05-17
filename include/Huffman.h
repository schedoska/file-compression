#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include "Image.h"

namespace Huffman
{
	struct Node
	{
		Node(int16_t value_, int freq_, Node* left_ = nullptr, Node* right_ = nullptr, bool isLeaf_ = false);
		int16_t value;
		int freq;
		Node* left;
		Node* right;
		bool isLeaf;
	};

	struct nodeComparator
	{
		bool operator()(const Node* node1, const Node* node2);
	};

	Node* GenerateTree(Image image);
	void GenerateDictionary(std::unordered_map<int16_t, std::string>& dictionary, Node* node, std::string code);
	void DeleteTree(Node* node);
	float MeanBitSize(std::unordered_map<int16_t, std::string>& dictionary, Image image);
}
