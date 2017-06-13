/**
 * @file DrawnObject.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 27 mars 2017
 */

#ifndef SRC_DRAWNOBJECT_H_
#define SRC_DRAWNOBJECT_H_

#include "LocalizedObject.h"

class World;

/**
 * @class DrawnObject
 * @brief This class is an interface for class that are drawn on OFX gui
 */
class DrawnObject: public LocalizedObject {
public:

	/**
	 * @brief Constructor
	 *
	 * Constructor of the DrawnObject class
	 *
	 * @param position : The initial position of the object
	 * @param theta : The initial rotation of the object
	 */
	DrawnObject(Vector3d position = Vector3d(), double theta = 0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the DrawnObject class
	 */
	virtual ~DrawnObject();

	/**
	 * @brief The projection function from real to pixel coordinates
	 *
	 * @param world : The World main coordinates frame
	 * @param p : The vector that will be projected
	 *
	 * @return The projected vector in pixel coordinates
	 */
	Vector3d real_to_pixel(World* world, Vector3d p);

	/**
	 * @brief The projection function from pixel to real coordinates
	 *
	 * @param world : The World main coordinates frame
	 * @param p : The vector that will be projected
	 *
	 * @return The projected vector in real coordinates
	 */
	Vector3d pixel_to_real(World* world, Vector3d p);

#ifdef USE_OFX
	virtual void draw(World* world) = 0;
#endif

};

#endif /* SRC_DRAWNOBJECT_H_ */
