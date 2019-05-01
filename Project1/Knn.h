#pragma once
class Knn
{
public: // methodes
	Knn();
	~Knn();
	std::string rob_knn(std::vector<float> testVector, std::vector<std::vector<float>> trainingData, std::vector<std::string> classes, int k);



private: // methodes
	void heapify(std::vector<float>& myVector, std::vector<int>& clInd, int n, int i);
	void heapSort(std::vector<float>& myVector, std::vector<int>& clInd);
	int string_pos(std::vector<std::string> myVector, std::string myString);

public:  // members


private: // members
};

