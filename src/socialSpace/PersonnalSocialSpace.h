/**
 * @file PersonnalSocialSpace.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 29 mars 2017
 */

#ifndef PERSONNALSOCIALSPACE_H_
#define PERSONNALSOCIALSPACE_H_

#include "SocialSpace.h"
#include "Agent.h"

/**
 * @class PersonnalSocialSpace
 * @brief This class is an interface to implement representation of a PersonnalSocialSpace
 *
 * This class is an interface to implement representation of the PersonnalSocialSpace of an Agent
 */
class PersonnalSocialSpace: public SocialSpace {
public:

	/**
	 * @brief Constructor
	 *
	 * Constructor of the PersonnalSocialSpace class
	 *
	 * @param agent : The Agent related to the PersonnalSocialSpace
	 * @param id : The unique identifier of the SocialSpace
	 */
	PersonnalSocialSpace(Agent * agent, int id = 0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the PersonnalSocialSpace class
	 */
	virtual ~PersonnalSocialSpace();

protected:
	Agent * _agent; //!< The Agent related to the PersonnalSocialSpace
};

#endif /* PERSONNALSOCIALSPACE_H_ */
