#pragma once
#include <vector>
#include <armadillo>
#include <math.h>
using namespace std;

class NeuralNetwork{
public:
	arma::mat w0;
	arma::mat w1;

	float fitness;

	int inputLayer;
	int hiddenLayer;
	int outputLayer;

	void printNetwork();

	void initialize();

	float sigmoid(float x);

	arma::mat feedForward(arma::mat input, int sampleSize);

	void saveNetwork(string levelName);
	NeuralNetwork loadNetwork(string levelName);
};