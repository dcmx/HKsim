/*
 * simulation.h
 *
 */

#ifndef SRC_SIMULATION_H_
#define SRC_SIMULATION_H_

#include "nxWindow/nxWindow.h"
#include "node.h"
#include <vector>
#include <random>
#include <iomanip>
#include <sstream>

typedef std::mt19937_64 randomEngine;

using namespace nx;

class Simulation: public Layer {
public:
	Simulation(randomEngine* random, Window* window) :
			Layer(), random(random), window(window), mode('a'), selected(NULL), move(NULL), edge(NULL), showSelected(true), oneDimension(false), showDashed1(
					true), showDashed2(true), showPotential(false), pointsize(8), linewidth(1) {
	}
	~Simulation() {

	}

	void addNode() {
		nodes.push_back(new node(window->getMousePosition()));
	}

	void addNode(vector position) {
		nodes.push_back(new node(position));
	}

	void addEdge() {
		if (nodes.size() < 2 || selected == NULL || edge == NULL)
			return;
		selected->addNeighbor(edge);
		edge->addNeighbor(selected);
	}
	void addEdge(unsigned int i, unsigned int j) {
		if (i < nodes.size() && j < nodes.size() && i != j) {
			nodes[i]->addNeighbor(nodes[j]);
			nodes[j]->addNeighbor(nodes[i]);
		}
	}
	void addAllEdges() {
		if (nodes.size() < 2 || selected == NULL)
			return;
		for (auto edge : nodes) {
			selected->addNeighbor(edge);
			edge->addNeighbor(selected);
		}
	}

	void updateRandom() {
		std::uniform_int_distribution<int> distribution(0, nodes.size() - 1);
		nodes[distribution(*random)]->update(oneDimension);
	}

	void mouseMove() {
		if (move != NULL) {
			move->setPosition(window->getMousePosition());
		}
		if (nodes.size() == 0)
			return;
		selected = nodes.front();
		vector where = window->getMousePosition();
		double dist = (selected->getPosition() - where).length2();
		for (auto node : nodes) {
			const double newDist = (node->getPosition() - where).length2();
			if (newDist < dist) {
				selected = node;
				dist = newDist;
			}
		}
		if (nodes.size() == 1)
			return;
		dist = 1e100;
		edge = NULL;
		for (auto node : nodes) {
			if (node == selected)
				continue;
			if (geometry::inBetween(where, selected->getPosition(), node->getPosition())) {
				double newDist = geometry::pointLineDistance(where, selected->getPosition(), node->getPosition());
				if (newDist < dist) {
					edge = node;
					dist = newDist;
				}
			}
		}
	}
	void mouseDown() {
		if (oneDimension) {
			window->setCenter(vector(window->getCenter().x, 0.0));
		}

	}

	void draw() {
		LineWidth((double) linewidth).draw();
		PointSize((double) pointsize).draw();

		if (oneDimension) {
			colors::black.set();
			Line(vector(-10000 * window->getPixelLength(), 0.0), vector(10000 * window->getPixelLength(), 0.0)).draw();

			double mousex = window->getMousePosition().x;
			Line(vector(mousex, -5.0 * window->getPixelLength()), vector(mousex, 5.0 * window->getPixelLength())).draw();
		}
		for (auto node : nodes) {
			colors::black.set();

			Point(node->getPosition()).draw();

			if (oneDimension) {
				colors::Color(0.0,0.0,0.0,0.05).set();
				vector c(node->getPosition().x, -5.0 * window->getPixelLength());
				DiskSector(c, c + vector(0.5,0.0),c+vector(-0.5,0.0),false).draw();
				colors::black.set();
				Line(vector(node->getPosition().x, -5.0 * window->getPixelLength()), vector(node->getPosition().x, 5.0 * window->getPixelLength())).draw();

			}
			colors::lightgrey.set();
			for (auto otherNode : nodes) {
				if (otherNode <= node)
					continue;
				if (((otherNode->getPosition() - node->getPosition()).length2() <= 1.0 && !oneDimension)
						|| (std::fabs(otherNode->getPosition().x - node->getPosition().x) <= 1.0 && oneDimension)) {
					Line(node->getPosition(), otherNode->getPosition()).draw();
				} else {
					if (showDashed1)
						DashedLine(node->getPosition(), otherNode->getPosition()).draw();
				}
			}
			colors::black.set();
			LineWidth(2.0 * (double) linewidth).draw();
			for (auto neighbor : node->getNeighbors()) {
				if (neighbor <= node)
					continue;
				if (((neighbor->getPosition() - node->getPosition()).length2() <= 1.0 && !oneDimension)
						|| (std::fabs(neighbor->getPosition().x - node->getPosition().x) <= 1.0 && oneDimension)) {
					Line(node->getPosition(), neighbor->getPosition()).draw();
				} else {
					if (showDashed2)
						DashedLine(node->getPosition(), neighbor->getPosition()).draw();
				}
			}
			LineWidth((double) linewidth).draw();
			if (showSelected) {
				colors::red.set();
				if (selected != NULL) {
					Point(selected->getPosition()).draw();
				}
				if (selected != NULL && edge != NULL) {
					Line(selected->getPosition(), edge->getPosition()).draw();
				}
			}

			if (move) {
				colors::green.set();
				Point(move->getPosition()).draw();
			}
		}
		if (showPotential) {
			TextLayer tl(colors::black);
			double pot = 0.0;

			for (auto node : nodes) {
				int count = 1;
				vector newPosition = node->getPosition();
				for (auto neighbor : node->getNeighbors()) {
					if (((neighbor->getPosition() - node->getPosition()).length2() <= 1.0 && !oneDimension)
							|| (std::fabs(neighbor->getPosition().x - node->getPosition().x) <= 1.0 && oneDimension)) {
						newPosition += neighbor->getPosition();
						++count;
					}
				}
				newPosition = newPosition / (double) count;
				if (oneDimension)
					pot += std::fabs(node->getPosition().x - newPosition.x);
				else
					pot += (node->getPosition() - newPosition).length();

			}
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << pot;
			tl.write(window->getOffset() + vector(10.0 * window->getPixelLength(), 10.0 * window->getPixelLength()), ss.str());
			tl.draw();
		}
	}

	void key(int key) {
		mouseMove();
		switch (key) {
		case 'p':
			pointsize = (pointsize * 2);
			if (pointsize >= 64)
				pointsize = 1;
			break;
		case 'l':
			linewidth = linewidth + 1;
			if (linewidth > 10)
				linewidth = 1;
			break;
		case 's':
			showSelected = !showSelected;
			break;
		case 'h':
			showDashed1 = !showDashed1;
			break;
		case 'H':
			showDashed2 = !showDashed2;
			break;
		case 'P':
			showPotential = !showPotential;
			break;
		case 'd':
			oneDimension = !oneDimension;
			if (oneDimension)
				mouseDown();
			break;
		case ' ':
			updateRandom();
			break;
		case 'G':
			for (auto node : nodes) {
				selected = node;
				addAllEdges();
			}
			break;
		default:
			mode = key;
		}
	}
	void click(int button) {
		mouseMove();
		if (button != 0) {
			mouseDown();
			return;
		}

		if (move != NULL) {
			move = NULL;
			return;
		}
		switch (mode) {
		case 'a':
			addNode();
			mouseMove();
			break;
		case 'e':
			addEdge();
			break;
		case 'E':
			addAllEdges();
			break;
		case 'u':
			if (selected != NULL)
				selected->update(oneDimension);
			break;
		default:
			if (selected != NULL)
				move = selected;
			break;
		}

	}
private:
	randomEngine* random;
	Window* window;
	int mode;
	std::vector<node*> nodes;
	node* selected;
	node* move;
	node* edge;
	bool showSelected;
	bool oneDimension;
	bool showDashed1;
	bool showDashed2;
	bool showPotential;
	int pointsize;
	int linewidth;
};



#endif /* SRC_SIMULATION_H_ */
