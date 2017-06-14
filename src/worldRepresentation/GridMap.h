/**
 * @file GridMap.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 6 avril 2017
 */

#ifndef SRC_GRIDMAP_H_
#define SRC_GRIDMAP_H_

#include "GridCell.h"
#include "World.h"
#include "Population.h"
#include "ofMain.h"

/**
 * @class GridMap
 *
 * This class manage the 2D GridMap computed from the Agents SocialSpace
 */
class GridMap: public IdentifiedObject, public DrawnObject{
public:
	/**
	 * @brief Constructor
	 *
	 * Constructor of the GridMap class
	 *
	 * @param world : The main frame coordinates
	 * @param pop : The population related to this GridMap
	 * @param resolution : The resolution of the GridMap, must be a fraction of the World width and height
	 */
	GridMap(World* world, Population* pop, double resolution = 0.1);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the GridMap class
	 */
	virtual ~GridMap();

#if USE_OFX
	/**
	 * @brief Openframeworks GUI drawing for visualization
	 *
	 * @param world : The main frame coordinates
	 */
	void draw(World* world);
#endif

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

	/**
	 * @brief Simple setter
	 * @param infoEnabled
	 */
	void setInfoEnabled(bool infoEnabled = false);

	/**
	 * @brief Simple getter
	 * @return groupSpaceEnabled
	 */
	bool isGroupSpaceEnabled() const;

	/**
	 * @brief Simple setter
	 * @param groupSpaceEnabled
	 */
	void setGroupSpaceEnabled(bool groupSpaceEnabled = true);

	/**
	 * @brief Simple getter
	 * @return personalSpaceEnabled
	 */
	bool isPersonalSpaceEnabled() const;

	/**
	 * @brief Simple setter
	 * @param personalSpaceEnabled
	 */
	void setPersonalSpaceEnabled(bool personalSpaceEnabled = true);

	/**
	 * @brief Simple getter
	 * @return borderEnabled
	 */
	bool isBorderEnabled() const;

	/**
	 * @brief Simple setter
	 * @param borderEnabled
	 */
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
