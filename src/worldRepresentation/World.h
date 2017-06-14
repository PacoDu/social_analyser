/*
 * World.h
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#ifndef SRC_WORLD_H_
#define SRC_WORLD_H_

#include "DrawnObject.h"
#include "config.h"

/**
 * @class World
 * @brief This class represent the main frame coordinates and its projection in pixels
 */
class World: public DrawnObject {
public:
	/**
	 * @brief Constructor
	 *
	 * Constructor of the World class
	 *
	 * @param width : The real width of the World in meter
	 * @param height : The real height of the World in meter
	 * @param widthView : The projection width of the World in pixel
	 * @param heightView : The projection height of the World in pixel
	 * @param position : The position of the World in the GUI in pixel
	 * @param theta : The rotation of the World in the GUI in radian
	 */
	World(double width, double height, int widthView, int heightView, Vector3d position = Vector3d(), double theta = 0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the World class
	 */
	virtual ~World();

#if USE_OFX
	/**
	 * @brief Openframeworks GUI drawing for visualization
	 *
	 * @param world : The main frame coordinates, this
	 */
	void draw(World* world);

	/**
	 * @brief Openframeworks GUI drawing for visualization
	 *
	 * Alias to the draw function with world parameter
	 */
	void draw();
#endif

	/**
	 * @brief Simple getter
	 * @return height
	 */
	double getHeight() const;

	/**
	 * @brief Simple setter
	 * @param height
	 */
	void setHeight(double height);

	/**
	 * @brief Simple getter
	 * @return heightView
	 */
	double getHeightView() const;

	/**
	 * @brief Simple setter
	 * @param heightView
	 */
	void setHeightView(double heightView);

	/**
	 * @brief Simple getter
	 * @return width
	 */
	double getWidth() const;

	/**
	 * @brief Simple setter
	 * @param width
	 */
	void setWidth(double width);

	/**
	 * @brief Simple getter
	 * @return widthView
	 */
	double getWidthView() const;

	/**
	 * @brief Simple setter
	 * @param widthView
	 */
	void setWidthView(double widthView);

	double width; //!< The real width of the World in meter
	double height; //!< The real height of the World in meter
	double widthView; //!< The projection width of the World in pixel
	double heightView; //!< The projection height of the World in pixel

};

#endif /* SRC_WORLD_H_ */
