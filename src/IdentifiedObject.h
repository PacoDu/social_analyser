/*
 * IdentifiedObject.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_IDENTIFIEDOBJECT_H_
#define SRC_IDENTIFIEDOBJECT_H_

class IdentifiedObject {
public:
	IdentifiedObject(unsigned int id);
	IdentifiedObject();
	virtual ~IdentifiedObject();

	unsigned int getId() const {
		return id;
	}

	void setId(unsigned int id) {
		this->id = id;
	}

protected:
	unsigned int id;
};

#endif /* SRC_IDENTIFIEDOBJECT_H_ */
