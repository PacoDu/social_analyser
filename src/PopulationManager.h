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
	// --- CONSTRUCTOR & DESTRUCTOR
	PopulationManager();
	PopulationManager(std::string feature_file, double x=0, double y=0);
	PopulationManager(std::string feature_file, std::string gt_file, double x=0, double y=0);

	~PopulationManager();

	// --- METHOD
	int loadFrame(unsigned int fIndex);
	int loadJson();
	int loadFeatureJson();
	int loadGroundTruthJson();

	int nextFrame();
	int previousFrame();

	void draw(double x, double y);
	const Population*& getPopulation() const;
	void setPopulation(const Population*& population);
	const std::string& getFeatureFile() const;
	void setFeatureFile(const std::string& featureFile);
	const ofxJSONElement& getFeatures() const;
	void setFeatures(const ofxJSONElement& features);
	unsigned int getFrameIndex() const;
	void setFrameIndex(unsigned int frameIndex = 0);
	const ofxJSONElement& getGroundTruth() const;
	void setGroundTruth(const ofxJSONElement& groundTruth);
	bool isGtEnabled() const;
	void setGtEnabled(bool gtEnabled = 0);
	const std::string& getGtFile() const;
	void setGtFile(const std::string& gtFile);
	bool isLoaded() const;
	void setLoaded(bool loaded = 0);

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
