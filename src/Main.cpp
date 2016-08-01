#include <SFML/Graphics.hpp>
#include <vector>
#include <armadillo>
#include <bitset>

#include "Level.h"
#include "Tile.h"
#include "Player.h"
#include "Debug.h"
#include "NeuralNetwork.h"
#include "Main.h"
#include "GeneticAlgorithm.h"

using namespace std;
using namespace arma;

int main() {

	//Window settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	//Main window dimensions
	float windowWidth = 1920 * 0.7;
	float windowHeight = 1080 * 0.7;
	  
	//Main window
	sf::RenderWindow mainWindow(sf::VideoMode(windowWidth, windowHeight), "Main", sf::Style::Default, settings);
	mainWindow.setPosition(sf::Vector2i(500, 100));
	mainWindow.setVerticalSyncEnabled(true);
	mainWindow.setFramerateLimit(120);

	//Tilemap window
	sf::RenderWindow tilemapWindow(sf::VideoMode(400, 400), "Tilemap", sf::Style::Default, settings);
	tilemapWindow.setPosition(sf::Vector2i(0, 0));
	tilemapWindow.setVerticalSyncEnabled(true);

	//Network window
	sf::RenderWindow networkWindow(sf::VideoMode(400, 400), "Network", sf::Style::Default, settings);
	networkWindow.setPosition(sf::Vector2i(0, 500));
	networkWindow.setVerticalSyncEnabled(true);
	
	//Game components 
	Level level = Level("level1.png", 64);
	Player player = Player(sf::Vector2f(256, 64), 64);

	//Main window view
	sf::View view;
	view.setCenter(player.position);
	view.setSize(windowWidth * 2, windowHeight * 2);
	mainWindow.setView(view);

	//Genetic algorithm to train player
	GeneticAlgorithm ga;

	//Generate initial population of networks
	ga.generationSize = 20;
	ga.generatePopulation();
	//ga.printGeneration();

	//Current generation sample index
	int currentSampleIndex = 0;

	//Player clock
	float lastX = -128;
	sf::Clock clock;

	//Current player fitness
	float fitness = 0;

	//Application loop
	while (mainWindow.isOpen()){

		//Main window event handler
		sf::Event event;
		while (mainWindow.pollEvent(event)){
			
			//Handle closing operation
			if (event.type == sf::Event::Closed)mainWindow.close();

			//Key pressed event
			if (event.type == sf::Event::KeyPressed) {

				//Continue testing and calculate fitness
				player.position = sf::Vector2f(256, 64);
				ga.generation[currentSampleIndex].fitness = fitness;
				fitness = 0;
				currentSampleIndex++;
			}
		}

		//Update lastX
		lastX = player.position.x;

		if (player.position.x > fitness){
			fitness = player.position.x;
		}

		if (lastX < player.position.x - 6 || lastX > player.position.x + 6) {
			clock.restart();
		}

		//Check if player is stuck
		if (clock.getElapsedTime().asSeconds() >= 5) {
			
			//Continue testing and calculate fitness
			ga.generation[currentSampleIndex].fitness = fitness;

			if (fitness > 600) {
				clock.restart();
			}

			if (fitness > 1000) {
				clock.restart();
			}

			if (fitness > 1400) {
				clock.restart();
			}

			if (fitness > 1800) {
				clock.restart();
			}

			if (fitness > 1000) {
				cout << "FIRST OBSACTLE COMPLETED WITH A FITNESS OF: " << fitness << endl;
			}
			else {
				cout << "Controller terminated with fitness: " << fitness << endl;
			}
			
			fitness = 0;
			
			player.position = sf::Vector2f(256, 64);
			currentSampleIndex++;

			//Reset the clock
			clock.restart();
		}

		//Network window
		networkWindow.clear(sf::Color::Black);
		networkWindow.display();

		//Tilemap window
		tilemapWindow.clear(sf::Color::Black);
		sf::Vector2f start(player.position.x - (5 * 64), player.position.y - (5 * 64));
		mat test = level.getTilemapSample(start, sf::Vector2i(5, 5));

		//Network termination tests
		if (player.position.y > (level.size.y * level.tileSize)) {

			//Continue testing
			ga.generation[currentSampleIndex].fitness = fitness;
			cout << "Controller terminated with fitness: " << fitness << endl;
			fitness = 0;
			
			player.position = sf::Vector2f(256, 64);
			currentSampleIndex++;
			clock.restart();
		}

		//If the generation has completed testing 
		if (currentSampleIndex >= ga.generationSize - 1) {
			
			//Find highest preformers
			srand(time(NULL));
			NeuralNetwork base = ga.findHighestPreformer();

			/*
			* Inhibit early population convergence
			*/
			//NeuralNetwork mate = ga.generation[rand() % ga.generationSize];


			
			/*
			* Allow algorithm to converge around early generations
			*/
			NeuralNetwork mate = ga.findHighestPreformer(base.fitness);

			//Get average fitness
			float averageFitness = ga.averageGenerationFitness();

			cout << "Progressed to next generation, average fitness: " << averageFitness << endl;
			cout << "Generation top score: " << base.fitness << endl;
			cout << "Generation second score: " << mate.fitness << endl;

			//Create new generation from crossovers
			NeuralNetwork nextGenerationBase = ga.crossover(base, mate);
			ga.generatePopulation(nextGenerationBase);
			currentSampleIndex = 0;
			
			//ga.printGeneration();
		}

		//Movement prediction
		mat prediction = ga.generation[currentSampleIndex].feedForward(test, 10);
		string move = player.predictMovement(prediction);

		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				if (test(x, y) == 1.0) {
					sf::RectangleShape rectangle;
					rectangle.setPosition(x * 40, y * 40);
					rectangle.setSize(sf::Vector2f(40, 40));
					rectangle.setFillColor(sf::Color::Green);
					tilemapWindow.draw(rectangle);
				}
			}
		}
		
		tilemapWindow.display();

		//Predraw
		mainWindow.setView(view);
		mainWindow.clear(sf::Color::Black);

		//Drawing
		level.drawLevel(mainWindow);
		player.draw(mainWindow, view, level, move);

		//End drawing
		mainWindow.display();
	}
};


//TODO:: IMPLEMENT BETTER AABB COLLISION http://gamedevelopment.tutsplus.com/tutorials/basic-2d-platformer-physics-part-1--cms-25799
//TODO:: RENDER TO OPTIMIZED RENDER TEXTURE INSTEAD OF DIRECTLY PIPING IT TO THE WINDOW
//TODO:: LOGGING AND OTHER DEBUGGING
//TODO:: FULLSCREEN AND DEBUGGING OPTIONS
//TODO:: START AND FINISH TILES
//TODO:: NEURAL NETWORK AND GENETIC ALGORITHM IMPLEMENTATIONS
//TODO:: TILEMAP RECTANGLE SAMPLING
//TODO:: WEIGHT SAVING (SAVE AND LOAD HIGH PREFOMRING NETWORKS)