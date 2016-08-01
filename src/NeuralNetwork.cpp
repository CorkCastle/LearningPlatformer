#include <vector>
#include <armadillo>
#include <fstream>
#include "NeuralNetwork.h"

using namespace std;
using namespace arma;

void NeuralNetwork::initialize() {

	inputLayer = 100;
	hiddenLayer = 20; 
	outputLayer = 3; 

	arma_rng::set_seed_random();
	w0 = randn<mat>(inputLayer, hiddenLayer);
	w1 = randn<mat>(hiddenLayer, outputLayer);	
}; 

void NeuralNetwork::saveNetwork(string levelName) {
	ofstream file;
	file.open(levelName);
	
	for (int x = 0; x < w0.n_rows; x++) {
		for (int y = 0; y < w0.n_cols; y++) {
			
		}
	}

	for (int x = 0; x < w1.n_rows; x++) {
		for (int y = 0; y < w1.n_cols; y++) {
			
		}
	}

	file << w0;
	file.close();
};

//NeuralNetwork loadNetwork() {
//	return NeuralNetwork(2, 2, 2);
//}

void NeuralNetwork::printNetwork() {
	w0.print("W0");
	w1.print("W1");
};

//Sigmoid transfer function/activation function
float NeuralNetwork::sigmoid(float x) {
	return 1 / (1 + exp(-x));
};

mat NeuralNetwork::feedForward(mat input, int sampleSize) {

	//Vectorize input matrix
	mat l0(1, sampleSize * sampleSize);
	for (int x = 0; x < sampleSize; x++) {
		for (int y = 0; y < sampleSize; y++) {
			l0(0, y * sampleSize + x) = input(x, y);
		}
	}

	//Hiddenlayer
	mat l1 = l0 * w0;
	l1.for_each([](mat::elem_type& val) { val = 1 / (1 + exp(-val)); });
	
	//Outputlayer
	mat l2 = l1 * w1;

	l2(0, 0) = 1 / (1 + exp(-l2(0, 0)));
	l2(0, 1) = 1 / (1 + exp(-l2(0, 1)));
	l2(0, 2) = 1 / (1 + exp(-l2(0, 2)));

	//l2.for_each([](mat::elem_type& val) { val = 1 / (1 + exp(-val)); });
	return l2;
};