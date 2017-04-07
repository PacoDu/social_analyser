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
	GridCell(double size, int id = 0, Point p = Point(), double value = 0);
	virtual ~GridCell();

	// --- METHOD
	void draw(World* world);

	// --- Getter & Setter
	double getValue() const;
	void setValue(double value);
	double getSize() const;
	void setSize(double size);

protected:
	double _value;
	double _size;
};

#endif /* SRC_GRIDCELL_H_ */
