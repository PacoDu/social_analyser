/*
 * GridCell.h
 *
 *  Created on: Apr 6, 2017
 *      Author: paco
 */

#ifndef SRC_GRIDCELL_H_
#define SRC_GRIDCELL_H_

#include "World.h"
#include "IdentifiedObject.h"
#include "DrawnObject.h"

class GridCell: public IdentifiedObject, public DrawnObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	GridCell(double size, double value = 0, Vector3d p = Vector3d(), int id = 0);
	virtual ~GridCell();

	// --- METHOD
	void draw(World* world);

	// --- Getter & Setter
	double getValue() const;
	void setValue(double value);
	double getSize() const;
	void setSize(double size);
	bool isBorderEnabled() const;
	void setBorderEnabled(bool borderEnabled = true);
	double getAStarScore() const;
	void setAStarScore(int starScore);
	bool isCellSelected() const;
	void setCellSelected(bool cellSelected = true);
	bool isFrontier() const;
	void setFrontier(bool frontier = true);
	bool isProcessed() const;
	void setProcessed(bool processed = true);
	bool isGoal() const;
	void setGoal(bool goal = true);
	bool isStart() const;
	void setStart(bool start = true);

protected:
	double _value;
	double _size;
	bool borderEnabled = false;

	// tmp for astar
	double _aStarScore = -1;
	bool cellSelected = false;
	bool frontier = false;
	bool processed = false;
	bool goal = false;
	bool start = false;


};

#endif /* SRC_GRIDCELL_H_ */
