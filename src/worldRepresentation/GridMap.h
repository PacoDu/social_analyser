/*
 * GridMap.h
 *
 *  Created on: Apr 6, 2017
 *      Author: paco
 */

#ifndef SRC_GRIDMAP_H_
#define SRC_GRIDMAP_H_

#include "GridCell.h"
#include "World.h"
#include "Population.h"

class GridMap: public IdentifiedObject, public DrawnObject{
public:
	GridMap(World* world, Population* pop, double resolution = 0.1);
	virtual ~GridMap();

	void draw(World* world);
	void compute();
	void normalize();
	void update();

protected:
	double width;
	double height;
	double resolution;
	Population* _population;

private:
	std::vector<std::vector<GridCell*>> _map;
};

#endif /* SRC_GRIDMAP_H_ */
