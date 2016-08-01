#pragma once

#include <armadillo>
#include <vector>
#include <iostream>
#include <bitset>
#include <math.h>

#include "GeneticAlgorithm.h"
#include "NeuralNetwork.h"

using namespace std;
using namespace arma;

void GeneticAlgorithm::generatePopulation() {
	generation.clear();
	for (int i = 0; i < generationSize; i++) {
		NeuralNetwork net;
		net.initialize();
		generation.push_back(net);
	}
};

NeuralNetwork GeneticAlgorithm::findHighestPreformer() {

	NeuralNetwork highestPreformer = generation[0];

	for (NeuralNetwork network : generation) {
		if (network.fitness > highestPreformer.fitness) {
			highestPreformer = network;
		}
	}

	return highestPreformer;
};

NeuralNetwork GeneticAlgorithm::findHighestPreformer(float exclude) {

	NeuralNetwork highestPreformer = generation[0];

	for (NeuralNetwork network : generation) {
		if (network.fitness > highestPreformer.fitness && network.fitness != exclude) {
			highestPreformer = network;
		}
	}

	return highestPreformer;
};

NeuralNetwork GeneticAlgorithm::crossover(NeuralNetwork base, NeuralNetwork mate) {

	NeuralNetwork child;
	child.initialize();

	//First set of weights
	for (int x = 0; x < base.w0.n_rows; x++) {
		for (int y = 0; y < base.w0.n_cols; y++) {
			srand(time(NULL));
			float r = rand();

			if (r < 0.7) {
				child.w0(x, y) = base.w0(x, y);
			}
			else {
				child.w0(x, y) = mate.w0(x, y);
			}
			
		}
	}

	//Second set of weights
	for (int x = 0; x < base.w1.n_rows; x++) {
		for (int y = 0; y < base.w1.n_cols; y++) {
			srand(time(NULL));
			float r = rand();

			if (r < 0.7) {
				child.w1(x, y) = base.w1(x, y);
			}
			else {
				child.w1(x, y) = mate.w1(x, y);
			}
		}
	}

	return child;
};

void GeneticAlgorithm::printGeneration() {
	for (NeuralNetwork network : generation) {
		network.printNetwork();
	}
};

void GeneticAlgorithm::generatePopulation(NeuralNetwork base) {
	generation.clear();
	for (int i = 0; i < generationSize; i++) {
		generation.push_back(mutate(base, 0.8));
	}
};

float GeneticAlgorithm::averageGenerationFitness() {

	float sum = 0;

	for (NeuralNetwork network : generation) {
		sum += network.fitness;
	}

	return sum / generationSize;
};

NeuralNetwork GeneticAlgorithm::mutate(NeuralNetwork network, float mutationRate) {

	srand(time(NULL));
	float r = rand();
	arma_rng::set_seed_random();
	mat w0Mutation = randn<mat>(network.w0.n_rows, network.w0.n_cols);
	network.w0 %= w0Mutation;

	arma_rng::set_seed_random();
	mat w1Mutation = randn<mat>(network.w1.n_rows, network.w1.n_cols);
	network.w1 %= w1Mutation;

	//for (int x = 0; x < network.w0.n_rows; x++) {
	//	for (int y = 0; y < network.w0.n_cols; y++) {
	//		float mutationChance = rand();
	//		if (mutationChance < mutationRate) {
	//			network.w0(x, y) += rand() % (10 - (-10) + 1) + (-10);
	//		}
	//	}
	//}

	//for (int x = 0; x < network.w1.n_rows; x++) {
	//	for (int y = 0; y < network.w1.n_cols; y++) {
	//		float mutationChance = rand();
	//		if (mutationChance < mutationRate) {
	//			network.w1(x, y) += rand() % (10 - (-10) + 1) + (-10);
	//		}
	//	}
	//}
	return network;
};