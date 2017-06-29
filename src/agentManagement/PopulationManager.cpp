/*
 * PopulationFactory.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: paco
 */

#include "PopulationManager.h"
#include "utils.h"
#include "ofxCsv.h"

// --- CONSTRUCTOR & DESTRUCTOR
PopulationManager::PopulationManager(World* world): DrawnObject(), world(world) {
	this->_population = new Population();
	map = new GridMap(this->world, this->_population, 0.1);
	map->setPersonalSpaceEnabled(false);
	map->setGroupSpaceEnabled(true);
	map->setBorderEnabled(false);
	map->update();

	gd = new GroupDetector(this->_population);

}
//
//PopulationManager::PopulationManager(World* world, std::string feature_file, Vector3d p):
//		DrawnObject(p), feature_file(feature_file), world(world) {
//	this->_population = new Population();
//	if(!this->loadFeatureJson()) this->loadFrame(frameIndex);
//
//	else throw std::string("Error while loading json file.");
//
//	this->findDataBounds();
//}

PopulationManager::PopulationManager(std::string feature_file,
		std::string gt_file, Vector3d p): DrawnObject(p), feature_file(feature_file), gt_file(gt_file) {

	this->_population = new Population();

//	this->setGtEnabled(1);
	this->findDataBounds();

	int w = round(max_x - min_x);
	int h = round(max_y - min_y);

	if(w!=h){
		if(w>h)
			h = w;
		else
			w = h;
	}

	this->world = new World(w,h, 600, 600, Vector3d(20,20,0), 0);
	ofLogNotice("DEBUG") << "World created width=" << world->getWidth() << " height=" << world->getHeight();

	map = new GridMap(this->world, this->_population, 0.1);
	map->setPersonalSpaceEnabled(true);
	map->setGroupSpaceEnabled(false);
	map->setBorderEnabled(true);
	map->update();


	int err = this->loadJson();
	if(!err) this->loadFrame(frameIndex);
	else ofLogError("PopulationManager::PopulationManager") << "Failed to load json";

	gd = new GroupDetector(this->_population);
	gd->detect(); // TODO Strange bug, if detect is done befor map init map is miss located with an Y offset
	map->update();
//	this->findDataBounds();

}

PopulationManager::~PopulationManager() {
	this->_population->clear();
	delete this->_population;
}


// --- METHOD
int PopulationManager::loadFrame(unsigned int fIndex) {
	ofLogNotice("DEBUG") << "Loading frame " << fIndex;
	if(!this->loaded){
		if(loadJson()){
			ofLogNotice("DEBUG") << "Error loading json frame#" << fIndex;
			return -1;
		}
	}

	this->_population->clear();
	this->_GT.clear();
//	this->_populationGT->clear();

	ofLogNotice("PopulationManager::loadFrame") << "Parsing features for frame #" << frameIndex;

	for (Json::ArrayIndex i = 0; i < features["features"][frameIndex].size(); ++i)
	{
//		Point pos;
//		if(min < 0){
//			pos.x = features["features"][frameIndex][i][1].asDouble() - min,
//
//		}
		Agent* a = new Agent(
						Vector3d(
								vProjection(features["features"][frameIndex][i][1].asDouble()/100, min_x, max_x, 0, world->getWidth()),
								vProjection(features["features"][frameIndex][i][2].asDouble()/100, min_y, max_y, 0, world->getHeight()),
								0
							),
						features["features"][frameIndex][i][3].asDouble(),
						features["features"][frameIndex][i][0].asInt()
						);
//		GaussianSpace * g = new GaussianSpace(a);
		this->_population->pushAgent(a);
	}

	if(this->isGtEnabled()){
		ofLogNotice("PopulationManager::loadFrame") << "Parsing ground truth for frame #" << frameIndex << " GTgroups size=" << groundTruth["GTgroups"].size();
		ofLogNotice("PopulationManager::loadFrame") << "GT size " << groundTruth["GTgroups"][frameIndex].size();
		int fId = 0;
		for (Json::ArrayIndex i = 0; i < groundTruth["GTgroups"][frameIndex].size(); ++i)
		{
			ofLogNotice("PopulationManager::loadFrame") << "Computing formation #" << i;
			std::vector<Agent*> group;
			for(Json::ArrayIndex j = 0; j < groundTruth["GTgroups"][frameIndex][i].size(); j++){
				group.push_back(this->_population->getAgent(groundTruth["GTgroups"][frameIndex][i][j].asInt()));
			}

			// TODO
			Formation* fformation = new Formation(group, fId);
//			fformation->computeSocialSpace(world);
			fId++;
			this->_GT.push_back(fformation);
		}
	}

//	gd->detect();
//	map->update();

	return 0;
}

void PopulationManager::update(){
//	this->_population->update(world);
	gd->detect();
	map->update();
}

int PopulationManager::loadJson() {
	int err = loadFeatureJson();
	if(!err && this->isGtEnabled()) err = loadGroundTruthJson();
	if(!err) this->loaded = 1;
	return err;
}

int PopulationManager::loadFeatureJson() {
	if(feature_file.length() > 0){
		bool parsingSuccessful = this->features.open(this->feature_file);
		if (parsingSuccessful) return 0;
		else{
			ofLogError("PopulationManager::loadFeatureJson")  << "Failed to parse features JSON" << std::endl;
		}
	}

	return -1;
}

int PopulationManager::loadGroundTruthJson() {
	if(gt_file.length() > 0){
		bool parsingSuccessful = this->groundTruth.open(this->gt_file);
		if (parsingSuccessful) return 0;
		else{
			ofLogError("PopulationManager::loadFeatureJson")  << "Failed to parse ground truth JSON" << std::endl;
		}
	}

	return -1;
}

void PopulationManager::runTest(){
	ofxCsv csvGT;
	ofxCsv csvResult;

	ofxJSONElement jsonResult;
	jsonResult.open("result.json");

	frameIndex = 0;
	int score = 0;
	for(int i = 0; i < features["features"].size();i++){
		loadFrame(frameIndex);
			update();

			ofLogNotice("GroundTruth") << " RESULT #######################";

			std::set<std::set<int>> gt;
			std::set<std::set<int>> detected;

			for(auto * f: this->_population->getFormations()){
				std::set<int> tmp;
				ofxCsvRow row;
				ofxJSONElement tmpJson;
				int k = 0;
				for(auto* a: f->getAgents()){
					row.setInt(k, a->getId());
					tmp.insert(a->getId());
					k++;
					tmpJson.append(a->getId());
				}
				csvResult.addRow(row);
				jsonResult["results"][i].append(tmpJson);
				detected.insert(tmp);
			}


			for(auto * f: this->_GT){
				std::set<int> tmp;
				ofxCsvRow row;
				int k = 0;
				for(auto* a: f->getAgents()){
					tmp.insert(a->getId());
					row.setInt(k, a->getId());
					k++;
				}
				csvGT.addRow(row);

				gt.insert(tmp);
			}

			if(gt ==  detected){
				ofLogNotice("HUURRAYAYYYY") << " GT is equal to detector";
				score++;
			}

			frameIndex++;
	}

	csvResult.save("result.csv");
	jsonResult.save("result2.json");
	csvGT.save("gt.csv");

	ofLogNotice("RESULT") << ((double)score)/frameIndex;

//
//	for(auto * f: this->_GT){
//		ofLogNotice("GroundTruth") << "Formation#" << f->getId();
//		for(auto * a: f->getAgents()){
//			ofLogNotice("GT") << "Agent#" << a->getId();
//		}
//	}
}

void PopulationManager::findDataBounds() {
	min_x = INFINITY;
	max_x = -INFINITY;

	min_y = INFINITY;
	max_y = -INFINITY;

	if(!this->loaded){
		if(loadJson()){
			ofLogNotice("DEBUG") << "Error loading json";
			return;
		}
	}


	for (Json::ArrayIndex i = 0; i < features["features"].size(); ++i){
		for (Json::ArrayIndex j = 0; j < features["features"][i].size(); ++j){
//			for (Json::ArrayIndex k = 0; k < features["features"][i][j].size(); ++k){
//				ofLogNotice("DEBUG") << "Agent#" <<  features["features"][i][j][0].asInt() << " x=" <<  features["features"][i][j][1].asDouble() << " y="  << features["features"][i][j][2].asDouble();
				if(features["features"][i][j][1].asDouble() > max_x) max_x = features["features"][i][j][1].asDouble();
				if(features["features"][i][j][1].asDouble() < min_x) min_x = features["features"][i][j][1].asDouble();
				if(features["features"][i][j][2].asDouble() > max_y) max_y = features["features"][i][j][2].asDouble();
				if(features["features"][i][j][2].asDouble() < min_y) min_y = features["features"][i][j][2].asDouble();
//			}
		}
	}

	min_x /= 100;
	min_y /= 100;
	max_y /= 100;
	max_x /= 100;
}


int PopulationManager::nextFrame() {
	if(frameIndex < features["features"].size()) frameIndex++;
	return this->loadFrame(frameIndex);
}

int PopulationManager::previousFrame() {
	if(frameIndex > 0) frameIndex--;
	return this->loadFrame(frameIndex);
}

void PopulationManager::draw(World* world) {
	this->world->draw();
	this->map->draw(this->world);
	this->_population->draw(this->world);
}

// --- Getter & Setter
Population* PopulationManager::getPopulation() const {
	return _population;
}

void PopulationManager::setPopulation(Population* population) {
	_population = population;
}

const std::string& PopulationManager::getFeatureFile() const {
	return feature_file;
}

void PopulationManager::setFeatureFile(const std::string& featureFile) {
	feature_file = featureFile;
}

const ofxJSONElement& PopulationManager::getFeatures() const {
	return features;
}

void PopulationManager::setFeatures(const ofxJSONElement& features) {
	this->features = features;
}

unsigned int PopulationManager::getFrameIndex() const {
	return frameIndex;
}

void PopulationManager::setFrameIndex(unsigned int frameIndex) {
	this->frameIndex = frameIndex;
}

const ofxJSONElement& PopulationManager::getGroundTruth() const {
	return groundTruth;
}

void PopulationManager::setGroundTruth(const ofxJSONElement& groundTruth) {
	this->groundTruth = groundTruth;
}

bool PopulationManager::isGtEnabled() const {
	return gt_enabled;
}

void PopulationManager::setGtEnabled(bool gtEnabled) {
	gt_enabled = gtEnabled;
}

const std::string& PopulationManager::getGtFile() const {
	return gt_file;
}

void PopulationManager::setGtFile(const std::string& gtFile) {
	gt_file = gtFile;
}

bool PopulationManager::isLoaded() const {
	return loaded;
}

void PopulationManager::setLoaded(bool loaded) {
	this->loaded = loaded;
}

void PopulationManager::findInteraction() {
	double pot = 0;
	Formation * target;
	for(auto * f: this->_population->getFormations()){
		if(f->getInteractionPotential() > pot){
			pot = f->getInteractionPotential();
			target = f;
		}
	}

	map->findPath(map->getCell(0,0), map->getCell(target->getInteractionPosition().x(), target->getInteractionPosition().y()));
}

World* PopulationManager::getWorld() const{
	return world;
}

GridMap* PopulationManager::getMap() const {
	return map;
}

Formation* PopulationManager::getHighestFormationInteractionPotential() {
	Formation * selectedForm = nullptr;
	double highestPot = 0;

	for(auto * f: _population->getFormations()){
		if(f->getInteractionPotential() > highestPot && map->getCell(f->getInteractionPosition().x(), f->getInteractionPosition().y())){
			selectedForm = f;
			highestPot = f->getInteractionPotential();
		}
	}

	return selectedForm;
}

//void PopulationManager::setWorld(const World*& world) {
//	this->world = world;
//}
