/**
 * @file IdentifiedObject.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 27 mars 2017
 */

#ifndef SRC_IDENTIFIEDOBJECT_H_
#define SRC_IDENTIFIEDOBJECT_H_

/**
 * @class IdentifiedObject
 * @brief This class is an interface for class that need a unique identifier
 */
class IdentifiedObject {
public:
	/**
	 * @brief Constructor
	 *
	 * Constructor of the IdentifiedObject class
	 *
	 * @param id : The unique identifier of the object
	 */
	IdentifiedObject(unsigned int id=0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the IdentifiedObject class
	 */
	virtual ~IdentifiedObject();

	/**
	 * @brief Simple getter
	 * @return id
	 */
	unsigned int getId() const;

	/**
	 * @brief Simpler setter
	 * @param id
	 */
	void setId(unsigned int id);

protected:
	unsigned int id; //!< The unique identifier
};

#endif /* SRC_IDENTIFIEDOBJECT_H_ */
