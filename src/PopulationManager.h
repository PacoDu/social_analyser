/*
 * PopulationFactory.h
 *
 *  Created on: Mar 28, 2017
 *      Author: paco
 */

#ifndef SRC_POPULATIONMANAGER_H_
#define SRC_POPULATIONMANAGER_H_

#include "ofxJSON.h"

#include "DrawnObject.h"
#include "Population.h"
#include "Agent.h"
#include "Formation.h"

class PopulationManager: public DrawnObject {
public:
	PopulationManager();
	PopulationManager(std::string feature_file, double x=0, double y=0);
	PopulationManager(std::string feature_file, std::string gt_file, double x=0, double y=0);

	~PopulationManager();

	int loadFrame(unsigned int fIndex);
	int loadJson();
	int loadFeatureJson();
	int loadGroundTruthJson();

	int nextFrame();
	int previousFrame();

	void draw(double x, double y);

	const std::string& getFeatureFile() const {
		return feature_file;
	}

	void setFeatureFile(const std::string& featureFile) {
		feature_file = featureFile;
	}

	unsigned int getFrameIndex() const {
		return frameIndex;
	}

	void setFrameIndex(unsigned int frameIndex = 0) {
		this->frameIndex = frameIndex;
	}

	const std::string& getGtFile() const {
		return gt_file;
	}

	void setGtFile(const std::string& gtFile) {
		gt_file = gtFile;
	}

	bool isGtEnabled() const {
		return gt_enabled;
	}

	void setGtEnabled(bool gtEnabled = 0) {
		gt_enabled = gtEnabled;
	}

protected:
	Population* _population;

	ofxJSONElement features;
	ofxJSONElement groundTruth;
	std::string feature_file;
	std::string gt_file;

	bool loaded = 0;
	bool gt_enabled = 0;
	unsigned int frameIndex = 0;
};

#endif /* SRC_POPULATIONMANAGER_H_ */
