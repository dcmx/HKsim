#include "nxWindow/nxWindow.h"
#include "geometry.h"
#include "node.h"
#include "simulation.h"

#include <iostream>

#include <random>
#include <thread>

typedef std::mt19937_64 randomEngine;

using namespace nx;

void readInput(Simulation* control) {
	double x = 0.0, y = 0.0;

	while (std::cin >> x >> y) {
		control->addNode(vector(x, y));
		std::cin.get();
		char c2 = std::cin.peek();
		if (c2 == '\n')
			break;
	}
	unsigned int i = 0, j = 0;
	while (std::cin >> i >> j) {
		control->addEdge(i, j);
	}
}

int main(int argc, char** argv) {

	std::random_device rd;
	std::mt19937_64 random(rd());

	Window window("Hegselmann Krause Simulation");
	window.setZoomBounds(20, 0.05);

	Simulation* control = new Simulation(&random, &window);
	std::thread input(readInput, control);

	colors::Color lightblue(0.0, 0.5, 1.0, 0.05);
	Overlay* ol = new Overlay(colors::lightgrey, 1);
	ol->addPrimitive(new Circle(vector(0.0, 0.0), 1.0));
	DrawLayer* dl = new DrawLayer(lightblue);
	dl->addPrimitive(new Disk(vector(0.0, 0.0), 1.0));
	ol->addLayer(dl);
	window.addLayer(ol);

	window.addLayer(control);
	window.show();
	input.detach();
	return EXIT_SUCCESS;
}
