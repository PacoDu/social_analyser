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
#include "ofMain.h"

class GridMap: public IdentifiedObject, public DrawnObject{
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	GridMap(World* world, Population* pop, double resolution = 0.1);
	virtual ~GridMap();

	// --- METHOD
	void draw(World* world);
	void compute();
	void normalize();
	void update();
	void deselectCells();
	int pathFinderNextStep();
	void resetCellColor();
	std::vector<GridCell*> constructPath();
	std::vector<GridCell*> neighbors(GridCell* cell, bool allowDiagonalMove = true);
	std::vector<GridCell*> findPath(GridCell* startCell, GridCell* endCell);
	GridCell* getCell(int cellId);
	GridCell* getCell(double x, double y);

	void setInfoEnabled(bool infoEnabled = false);

	// --- Getter & Setter
	bool isGroupSpaceEnabled() const;
	void setGroupSpaceEnabled(bool groupSpaceEnabled = true);
	bool isPersonalSpaceEnabled() const;
	void setPersonalSpaceEnabled(bool personalSpaceEnabled = true);
	bool isBorderEnabled() const;
	void setBorderEnabled(bool borderEnabled = true);

protected:
	Population* _population;
	double width;
	double height;
	double resolution;
	double minValue;
	double maxValue;
	bool personalSpaceEnabled = true;
	bool groupSpaceEnabled = true;
	bool borderEnabled = false;
	bool infoEnabled = false;



	typedef std::pair<double, GridCell*> VCell;

	struct CompaireVCell
	{
	    bool operator()(VCell const& a, VCell const& b) const
	    {
	        return a.first > b.first;
	    }
	};

	std::priority_queue<VCell, std::vector<VCell>, CompaireVCell > openNodesPQ;
	std::map<GridCell*, GridCell*> cameFrom;
	std::map<GridCell*, double> gScore;
	GridCell* endCell;
	GridCell* startCell;

private:
	std::vector<std::vector<GridCell*>> _map;
};

#endif /* SRC_GRIDMAP_H_ */
