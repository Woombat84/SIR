#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>
#include "Knn.h"


Knn::Knn()
{
}


Knn::~Knn()
{
}


//this function returns the distance between 2 vectors.
//it is a template because it could take as arguments vectors of different types;
//the distance work by the formula d = sqrt((x1-x2)^2+(y1-y2)^2), but in multidimensions
template <typename T, typename D>
float  operator>>(const std::vector<T>& A, const std::vector<D>& B) {
	float sum = 0;
	if (A.size() != B.size())
		return 0;
	for (int i = 0; i < A.size(); i++)
		sum += ((float)A[i] - (float)B[i]) * ((float)A[i] - (float)B[i]);

	return sqrt(sum);
}


//returns a normalized vector (all values are between 0..1)
//it a template because it can take vectors of different types;
//it work by the formula (currentValue - min)/(max-min)
template <typename T>
std::vector<float> rob_normalize(const std::vector<T> & A)
{
	float min, max;
	min = A[0];
	max = A[0];
	//find the max and min values from the vector
	for (int i = 0; i < A.size(); i++) {
		if (A[i] > max)
			max = (float)A[i];
		if (A[i] < min)
			min = (float)A[i];

	}
	std::vector<float> AB;
	//applying the formula
	for (int i = 0; i < A.size(); i++)
		AB.push_back(((float)A[i] - min) / (float)(max - min));
	return AB;
}

void Knn::heapify(std::vector<float>& myVector, std::vector<int>& clInd, int n, int i) {
	int biggest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	//if left is larger than root
	if (l < n && myVector[l] > myVector[biggest])
		biggest = l;
	//if right is larger than root
	if (r < n && myVector[r] > myVector[biggest])
		biggest = r;

	// If largest is not root 
	if (biggest != i)
	{
		std::swap(myVector[i], myVector[biggest]);
		std::swap(clInd[i], clInd[biggest]);

		// Recursively heapify the affected sub-tree 
		heapify(myVector, clInd, n, biggest);
	}
}

void Knn::heapSort(std::vector<float>& myVector, std::vector<int>& clInd)
{
	// Build heap (rearrange array) 
	int n = myVector.size();
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(myVector, clInd, n, i);

	// One by one extract an element from heap 
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end
		std::swap(myVector[0], myVector[i]);
		std::swap(clInd[0], clInd[i]);

		// call max heapify on the reduced heap 
		heapify(myVector, clInd, i, 0);
	}
}

int Knn::string_pos(std::vector<std::string> myVector, std::string myString) {
	for (int i = 0; i < myVector.size(); i++)
		if (myString.compare(myVector[i]) == 0)
			return i;
	return -1;
}

std::string Knn::rob_knn(std::vector<float> testVector, std::vector<std::vector<float>> trainingData, std::vector<std::string> classes, int k) {
	std::vector<float> results;
	std::vector<int> classIndex;

	//puts in a vector all the distances between test Vector and training Data
	for (int i = 0; i < trainingData.size(); i++) {
		results.push_back(testVector >> trainingData[i]);
		classIndex.push_back(i);
	}
	//sorting the results, the same changes are did in classIndex
	heapSort(results, classIndex);
	std::vector<std::string> finalClasses;
	//getting the k classes from the sorted class Index, using it as index
	for (int i = 0; i < k; i++)
		finalClasses.push_back(classes[classIndex[i]]);

	std::vector<int> countVector;
	std::vector<std::string> difClass;
	//filling a vector of size k with 0
	for (int i = 0; i < k; i++)
		countVector.push_back(0);

	//makes a vector of different classes and counts the amount of their aparece in finalClasses
	for (int i = 0; i < finalClasses.size(); i++) {
		if (string_pos(difClass, finalClasses[i]) == -1)
			difClass.push_back(finalClasses[i]);
		countVector[string_pos(difClass, finalClasses[i])]++;
	}


	//gets the position of the more frecvent class
	int maxPos = 0;
	int max = countVector[0];
	for (int i = 0; i < difClass.size(); i++)
		if (countVector[i] > max) {
			max = countVector[i];
			maxPos = i;
		}
	return difClass[maxPos];

}
