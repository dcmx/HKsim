/*
 * node.h
 *
 */

#ifndef SRC_NODE_H_
#define SRC_NODE_H_

#include <vector>
#include "nxWindow/vector.h"
using nx::vector;

class node {
public:
	node() :
			position(0.0, 0.0), neighbors() {
	}
	node(vector position) :
			position(position), neighbors() {

	}
	inline void update(const bool oneDimension) {
		if (oneDimension)
			update1D();
		else
			update2D();
	}
	void update2Dold() {

		vector newPosition(position);
		int count = 1;
		for (node *neighbor : neighbors) {
			if ((neighbor->position - position).length2() <= 1.0) {
				newPosition += vector(neighbor->position.x, neighbor->position.y);
				count += 1;
			}
		}
		if (count > 1)
			position = newPosition / (double) count;
	}
	void update2D() {

		vector newPosition(position);
		double sum = 1.0;
		for (node *neighbor : neighbors) {
			if ((neighbor->position - position).length2() <= 1.0) {
				vector d = neighbor->position - position; //(position.x-neighbor->position.x,position.y-neighbor-position.y);
				double dlen = d.length();
				double f = std::sqrt(1.0 - dlen);
				newPosition += vector(f * neighbor->position.x, f * neighbor->position.y);
				sum += f;
			}
		}
		if (sum > 1.0)
			position = newPosition / sum;
	}
	void update1D() {

		double newPositionX = position.x;
		int count = 1;
		for (node *neighbor : neighbors) {
			if (std::fabs(neighbor->position.x - position.x) <= 1.0) {
				newPositionX += neighbor->position.x;
				count += 1;
			}
		}
		if (count > 1)
			position.x = newPositionX / (double) count;
	}

	void addNeighbor(node *other) {
		for (auto neighbor : neighbors)
			if (neighbor == other)
				return;
		if (this == other)
			return;
		neighbors.push_back(other);
	}
	vector getPosition() {
		return position;
	}
	void setPosition(vector const position) {
		this->position = position;
	}
	const std::vector<node*>& getNeighbors() const {
		return neighbors;
	}

private:
	vector position;
	std::vector<node*> neighbors;
	friend class vector;
};

#endif /* SRC_NODE_H_ */
