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
 * @brief This class manage the 2D GridMap computed from the Agents SocialSpace
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

	/**
	 * @brief Compute the value of each GridCell in the GridMap based on Agents SocialSpace
	 */
	void compute();

	/**
	 * @brief Normalize the GridCells value between 0 and 1
	 */
	void normalize();

	/**
	 * @brief Update the GridMap by calling compute and normalize function
	 */
	void update();

	/**
	 * @brief Set all GridCell to selected False
	 */
	void deselectCells();

	/**
	 * @brief Compute one step of the A* algorithm
	 * @return 1 if pathFinder reached goal, -1 pathFinder couldn't reach the goal, 0 otherwise
	 */
	int pathFinderNextStep();

	/**
	 * @brief Reset the color of all GridCell
	 */
	void resetCellColor();

	/**
	 * @brief Build the path from A* algorithm result
	 * @return List of GridCell representing the path found in the GridMap
	 */
	std::vector<GridCell*> constructPath();

	/**
	 * @brief Find the neighbors of a GridCell in the GridMap
	 *
	 * @param cell : Target GridCell
	 * @param allowDiagonalMove : Allow diagonal neighboring
	 *
	 * @return List of neighbors GridCell
	 */
	std::vector<GridCell*> neighbors(GridCell* cell, bool allowDiagonalMove = true);

	/**
	 * @brief Find path between two given GridCell in parameters
	 *
	 * @param startCell : The starting GridCell
	 * @param endCell : The goal GridCell
	 *
	 * @return The path found in the GridMap in a list of GridCell
	 */
	std::vector<GridCell*> findPath(GridCell* startCell, GridCell* endCell);

	/**
	 * @brief Get a GridCell in the GridMap by id
	 *
	 * @param cellId : The unique identifier of the GridCell
	 *
	 * @return The corresponding GridCell, null if not found
	 */
	GridCell* getCell(unsigned int cellId);

	/**
	 * @brief find a GridCell in the GridMap from its real coordinates
	 *
	 * @param x : The x coordinate of the GridCell in meter
	 * @param y : The y coordinate of the GridCell in meter
	 *
	 * @return The corresponding GridCell, null if not found
	 */
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
	Population* _population; //!< The Population related to the GridMap
	double width; //!< The real width of the GridMap in meter
	double height; //!< The real height of the GridMap in meter
	double resolution; //!< The resolution of the GridMap
	double minValue; //!< The minimum value of a GridCell in the GridMap
	double maxValue; //!< The maximum value of a GridCell in the GridMap
	bool personalSpaceEnabled = true; //!< Enable or disable the computing of the PersonalSocialSpace in the GridMap
	bool groupSpaceEnabled = true; //!< Enable or disable the computing of the GroupSocialSpace in the GridMap
	bool borderEnabled = false; //!< Enable or disable the drawing of the GridCell border
	bool infoEnabled = false; //!< Enable or disable the drawing of the GridCell information

	/**
	 * @typedef VCell
	 *
	 * @brief Define an operator for GridCell and associated gScore comparison for A* algorithm
	 */
	typedef std::pair<double, GridCell*> VCell;

	/**
	 * @struct CompaireVCell
	 *
	 * @brief Define an operator for GridCell and associated gScore comparison for A* algorithm
	 */
	struct CompaireVCell
	{
		/**
		 * @param a : The VCell compared
		 * @param b : The other VCell compared
		 * @return 1 if VCell have a greater score than the VCell b
		 */
	    bool operator()(VCell const& a, VCell const& b) const
	    {
	        return a.first > b.first;
	    }
	};

	std::priority_queue<VCell, std::vector<VCell>, CompaireVCell > openNodesPQ; //!< Priority queue for open nodes processing in A* algorithm
	std::map<GridCell*, GridCell*> cameFrom; //!< Path relation between GridCell for A* algorithm
	std::map<GridCell*, double> gScore; //!< The score obtained in A* algorithm associated to its GridCell
	GridCell* endCell; //!< The goal GridCell for the path
	GridCell* startCell; //!< The starting GridCell for the path

private:
	std::vector<std::vector<GridCell*>> _map; //!< The GridMap represented by list of GridCell
};

#endif /* SRC_GRIDMAP_H_ */
