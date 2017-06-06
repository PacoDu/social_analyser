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
#include "GaussianSpace.h"
#include "GridMap.h"
#include "GroupDetector.h"

class PopulationManager: public DrawnObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	PopulationManager(World* world);
	PopulationManager(World* world, std::string feature_file, Vector3d p = Vector3d());
	PopulationManager(std::string feature_file, std::string gt_file, Vector3d p = Vector3d());

	~PopulationManager();

	// --- METHOD
	int loadFrame(unsigned int fIndex);
	int loadJson();
	int loadFeatureJson();
	int loadGroundTruthJson();
	void findDataBounds();

	void runTest();

	int nextFrame();
	int previousFrame();

	void findInteraction();

	void draw(World* world);
	void update();

	// --- Getter & Setter
	Population* getPopulation() const;
	void setPopulation(Population* population);
	const std::string& getFeatureFile() const;
	void setFeatureFile(const std::string& featureFile);
	const ofxJSONElement& getFeatures() const;
	void setFeatures(const ofxJSONElement& features);
	unsigned int getFrameIndex() const;
	void setFrameIndex(unsigned int frameIndex);
	const ofxJSONElement& getGroundTruth() const;
	void setGroundTruth(const ofxJSONElement& groundTruth);
	bool isGtEnabled() const;
	void setGtEnabled(bool gtEnabled);
	const std::string& getGtFile() const;
	void setGtFile(const std::string& gtFile);
	bool isLoaded() const;
	void setLoaded(bool loaded);
	World* getWorld() const;
//	void setWorld(const World*& world);

protected:
	Population* _population;
	std::vector<Formation*> _GT;

	ofxJSONElement features;
	ofxJSONElement groundTruth;
	std::string feature_file;
	std::string gt_file;
	World* world;
	GridMap* map;
	GroupDetector* gd;

	double min_x, min_y, max_x, max_y;

	bool loaded = 0;
	bool gt_enabled = 1;
	unsigned int frameIndex = 0;
};

#endif /* SRC_POPULATIONMANAGER_H_ */
