/**
 * @file GridCell.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 6 avril 2017
 */

#ifndef SRC_GRIDCELL_H_
#define SRC_GRIDCELL_H_

#include "World.h"
#include "IdentifiedObject.h"
#include "DrawnObject.h"

/**
 * @class GridCell
 * @brief This class represent a cell in the GridMap
 */
class GridCell: public IdentifiedObject, public DrawnObject {
public:

	/**
	 * @brief Constructor
	 *
	 * Constructor of the GridCell class
	 *
	 * @param size : The size of the GridCell
	 * @param value : The initial value of the GridCell
	 * @param position : The position of the GridCell in real coordinate
	 * @param id : The unique identifier of the GridCell
	 */
	GridCell(double size, double value = 0, Vector3d position = Vector3d(), int id = 0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the GridCell class
	 */
	virtual ~GridCell();

#if USE_OFX
	/**
	 * @brief Openframeworks GUI drawing for visualization
	 *
	 * @param world : The main frame coordinates
	 */
	void draw(World* world);
#endif

	/**
	 * @brief Simple getter
	 * @return value
	 */
	double getValue() const;

	/**
	 * @brief Simple setter
	 * @param value
	 */
	void setValue(double value);

	/**
	 * @brief Simple getter
	 * @return size
	 */
	double getSize() const;

	/**
	 * @brief Simple setter
	 * @param size
	 */
	void setSize(double size);

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

	/**
	 * @brief Simple getter
	 * @return aStarScore
	 */
	double getAStarScore() const;

	/**
	 * @brief Simple setter
	 * @param starScore
	 */
	void setAStarScore(int starScore);

	/**
	 * @brief Simple getter
	 * @return cellSelected
	 */
	bool isCellSelected() const;

	/**
	 * @brief Simple setter
	 * @param cellSelected
	 */
	void setCellSelected(bool cellSelected = true);

	/**
	 * @brief Simple getter
	 * @return frontier
	 */
	bool isFrontier() const;

	/**
	 * @brief Simple setter
	 * @param frontier
	 */
	void setFrontier(bool frontier = true);

	/**
	 * @brief Simple getter
	 * @return processed
	 */
	bool isProcessed() const;

	/**
	 * @brief Simple setter
	 * @param processed
	 */
	void setProcessed(bool processed = true);

	/**
	 * @brief Simple getter
	 * @return goal
	 */
	bool isGoal() const;

	/**
	 * @brief Simple setter
	 * @param goal
	 */
	void setGoal(bool goal = true);

	/**
	 * @brief Simple getter
	 * @return start
	 */
	bool isStart() const;

	/**
	 * @brief Simple setter
	 * @param start
	 */
	void setStart(bool start = true);

	/**
	 * @brief Simple getter
	 * @return infoEnabled
	 */
	bool isInfoEnabled() const;

	/**
	 * @brief Simple setter
	 * @param infoEnabled
	 */
	void setInfoEnabled(bool infoEnabled = true);

protected:
	double _size; //!< The size of the GridCell
	double _value; //!< The value of the GridCell
	bool borderEnabled = false; //!< Enable of disable GridCell border drawing

	// tmp for astar
	double _aStarScore = -1; //!< The A* score of the GridCell
	bool cellSelected = false; //!< Select of deselect GridCell (change drawing color)
	bool frontier = false; //!< If the GridCell is a frontier (change drawing color)
	bool processed = false; //!< If the GridCell has been processed (change drawing color)
	bool goal = false; //!< If the GridCell is the goal to reach (change drawing color)
	bool start = false; //!< If the GridCell is the starting point (change drawing color)
	bool infoEnabled = false; //!< Enable of disable GridCell informations drawing

};

#endif /* SRC_GRIDCELL_H_ */
