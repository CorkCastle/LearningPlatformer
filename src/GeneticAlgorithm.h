#pragma once

#include <vector>
#include <armadillo>

#include "NeuralNetwork.h"

using namespace std;
using namespace arma;

class GeneticAlgorithm {
public:
	vector<NeuralNetwork> generation;
	int generationSize;

	void generatePopulation();
	void generatePopulation(NeuralNetwork base);
	void printGeneration();
	NeuralNetwork findHighestPreformer();
	NeuralNetwork findHighestPreformer(float exclude);
	float averageGenerationFitness();
	NeuralNetwork crossover(NeuralNetwork, NeuralNetwork);
	NeuralNetwork mutate(NeuralNetwork, float mutationRate);
};
