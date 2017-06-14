/**
 * @file SocialSpace.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 27 mars 2017
 */

#ifndef SRC_SOCIALSPACE_H_
#define SRC_SOCIALSPACE_H_

#include "IdentifiedObject.h"

/**
 * @class SocialSpace
 * @brief This class is an abstract class for representing SocialSpace
 */
class SocialSpace: public IdentifiedObject{
public:
	/**
	 * @brief Constructor
	 *
	 * Constructor of the SocialSpace class
	 *
	 * @param id : The unique identifier of the SocialSpace
	 */
	SocialSpace(int id = 0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the SocialSpace class
	 */
	virtual ~SocialSpace();

};

#endif /* SRC_SOCIALSPACE_H_ */
