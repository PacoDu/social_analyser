/**
 * @file GroupSocialSpace.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 29 mars 2017
 */

#ifndef GROUPSOCIALSPACE_H_
#define GROUPSOCIALSPACE_H_

#include "SocialSpace.h"
#include "AgentContainer.h"

/**
 * @class GroupSocialSpace
 * @brief This class is an interface to implement representation of a GroupSocialSpace
 *
 * This class is an interface to implement representation of the GroupSocialSpace of a Formation
 */
class GroupSocialSpace: public SocialSpace, public AgentContainer {
public:

	/**
	 * @brief Constructor
	 *
	 * Constructor of the GroupSocialSpace class, with no Agent
	 *
	 * @param id : The unique identifier of the GroupSocialSpace
	 */
	GroupSocialSpace(int id = 0);

	/**
	 * @brief Constructor
	 *
	 * Constructor of the GroupSocialSpace class, for the Agents in parameter
	 *
	 * @param agents : The Agents related to the GroupSocialSpace
	 * @param id : The unique identifier of the GroupSocialSpace
	 */
	GroupSocialSpace(std::vector<Agent*>& agents, int id = 0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the GroupSocialSpace class
	 */
	virtual ~GroupSocialSpace();

};

#endif /* GROUPSOCIALSPACE_H_ */
