#include "../include/Huffman.h"

namespace Huffman {
	Node::Node(int16_t value_, int freq_, Node* left_, Node* right_, bool isLeaf_)
	{
		value = value_;
		freq = freq_;
		left = left_;
		right = right_;
		isLeaf = isLeaf_;
	}

	Node* GenerateTree(Image image)
	{
		int h = image.GetHeight();
		int w = image.GetWidth();
		std::unordered_map<int16_t, int> freq;
		for (int x = 0; x < w; ++x) {
			for (int y = 0; y < h; ++y) {
				freq[image(x, y)]++;
			}
		}

		std::priority_queue<Node*, std::vector<Node*>, nodeComparator> nodesList;
		std::unordered_map<int16_t, int>::iterator it;
		for (it = freq.begin(); it != freq.end(); it++) {
			nodesList.push(new Node((*it).first, (*it).second, nullptr, nullptr, true));
		}
		while (nodesList.size() > 1)
		{
			Node* a = nodesList.top();
			nodesList.pop();
			Node* b = nodesList.top();
			nodesList.pop();
			nodesList.push(new Node(0, a->freq + b->freq, a, b));
		}

		return nodesList.top();
	}

	void GenerateDictionary(std::unordered_map<int16_t, std::string>& dictionary, Node* node, std::string code)
	{
		if (node == nullptr) return;
		if (node->isLeaf) dictionary[node->value] = code;
		else {
			GenerateDictionary(dictionary, node->left, code + '0');
			GenerateDictionary(dictionary, node->right, code + '1');
		}
	}

	void DeleteTree(Node* node)
	{
		if (node == nullptr) return;
		if (!node->isLeaf) {
			DeleteTree(node->left);
			DeleteTree(node->right);
		}
		delete node;
	}
	bool nodeComparator::operator()(const Node* node1, const Node* node2)
	{
		return node1->freq > node2->freq;
	}

	float MeanBitSize(std::unordered_map<int16_t, std::string>& dictionary, Image image)
	{
		std::unordered_map<int, int> histogram = image.HistogramData();
		double s = image.GetHeight() * image.GetWidth();
		double avg = 0;

		for(auto& it : histogram){
			double p = (float)it.second / s; 
			avg += p * dictionary[it.first].length();
		}
		return avg;
	}
}