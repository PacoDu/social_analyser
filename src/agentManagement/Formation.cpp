/**
 * @file Formation.cpp
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 24 mars 2017
 */

#include "Formation.h"
#include "config.h"
#include "utils.h"

#ifdef USE_OFX
	#include "ofMain.h"
#endif

// --- CONSTRUCTOR & DESTRUCTOR
Formation::Formation(std::vector<Agent*> agents , int id):
		IdentifiedObject(id), AgentContainer(agents){
	_socialSpace = new OSpace(agents);
}

Formation::Formation(int id): IdentifiedObject(id), AgentContainer(){
	_socialSpace = NULL; // TODO init empty OSpace ?
}

Formation::Formation(Agent* agent, int id):
		Formation(initAgent(agent), id){
}

Formation::~Formation() {
	if(_socialSpace) delete _socialSpace;
}

// --- METHOD
#ifdef USE_OFX
void Formation::draw(World* world) {
	_socialSpace->draw(world);

	// Coordinates projection
	Vector3d pView = real_to_pixel(world, interactionPosition);

	// Drawing
	ofPushMatrix();
		ofTranslate(pView.x(), pView.y());
		ofSetHexColor(0xFF0000);
		ofSetLineWidth(2.0f);
		ofDrawLine(0,0,-interactionDirection.x()*25,-interactionDirection.y()*25);
		ofSetHexColor(0x00FF00);
		ofDrawCircle(0, 0, 10);
	ofPopMatrix();

//	pView = real_to_pixel(world, this->_socialSpace->getCenter());
//	ofPushMatrix();
//		ofTranslate(pView.x(), pView.y());
//		ofSetHexColor(0xFFFFFF);
//		for(auto p: agentDir_ospace){
//			p *= 500;
//			ofDrawLine(0,0, p.x(), p.y());
//		}
//		ofSetHexColor(0xFF0000);
//		ofDrawLine(0,0, interactionDirection.x()*300, interactionDirection.y()*300);
//	ofPopMatrix();
}
#endif

void Formation::pushAgent(Agent* agent) {
	AgentContainer::pushAgent(agent);

	if(!this->_socialSpace)
		this->_socialSpace = new OSpace(this->_agents);
	else
		this->_socialSpace->pushAgent(agent);

//	this->_socialSpace->update();
}

void Formation::removeAgent(unsigned int agentId) {
	AgentContainer::removeAgent(agentId);

	this->_socialSpace->removeAgent(agentId);

//	this->_socialSpace->update();
}

void Formation::update() {
//	ofLogNotice("Formation::update") << "Updating social space for Formation#" << this->getId();
	this->_socialSpace->update();
	this->computeInteractionPotential();
	this->findInteractionPosition();
}

void Formation::computeInteractionPotential() {
	double meanInterPersoDist = 0;
	double meanCenterDist = 0;

	// Compute mean distances
	for(unsigned int i = 0; i < this->_agents.size(); i++){
		unsigned int neighborIndex = i+1;
		if(neighborIndex >= this->_agents.size()) neighborIndex = 0;

		meanInterPersoDist += distance(this->_agents[i]->getPosition(), this->_agents[neighborIndex]->getPosition());
		meanCenterDist += distance(this->_agents[i]->getPosition(), this->_socialSpace->getCenter()); // TODO Distance from gCenter would be better ??
	}

	meanInterPersoDist /= this->_agents.size();
	meanCenterDist /= this->_agents.size();

	// value projection between [0-1]
	interactionPotential = (tanh(meanInterPersoDist) + tanh(meanCenterDist))/2;
}

void Formation::findInteractionPosition() {
	// SocialSpace must be up to date (to use clock wise sorted agent vector)

	// Get clock wise sorted agents and gravity center of the formation
	std::vector<Agent*> sortedAgents = this->_socialSpace->getAgents();
	if(sortedAgents.size() <= 1) return;

	Vector3d gCenter = this->_socialSpace->getgCenter();

	// Compute vector gravity center -> agent
	agentDir_ospace.clear();
	for(auto * sA: sortedAgents){
		Vector3d aDir = sA->getPosition() - this->_socialSpace->getCenter();
		agentDir_ospace.push_back(aDir.normalized());
	}

	// Compute angle between Agents and find max angle
	double maxAngle = 0;
	int maxAngleIndex = -1;
	int maxNeighborAngleIndex = -1;

	// Two approach for angle mesure
	if(agentDir_ospace.size() > 2){
		for(unsigned int i = 0; i < agentDir_ospace.size(); i++){
			unsigned int neighborIndex = i+1;
			if(neighborIndex >= agentDir_ospace.size()) neighborIndex = 0;

			double aAngle = acos(
								agentDir_ospace[i].normalized().dot(
										agentDir_ospace[neighborIndex].normalized())
							);
			Vector3d crossP =
					agentDir_ospace[i].normalized().cross(agentDir_ospace[neighborIndex].normalized());

			if(Vector3d(0,0,1).dot(crossP) < 0) aAngle = -aAngle; // [0, 2PI]

			if(abs(maxAngle) < abs(aAngle)){
				maxAngle = aAngle;

				maxNeighborAngleIndex = neighborIndex;
				maxAngleIndex = i;
			}

//			ofLogNotice("Formation::findInteractionPosition")
//				<< "Angle(#" << sortedAgents[i]->getId() << ",#"
//				<< sortedAgents[neighborIndex]->getId() << ")=" << aAngle;
		}
	}
	else{
		for(unsigned int i = 0; i < agentDir_ospace.size(); i++){
			unsigned int neighborIndex = i+1;
			if(neighborIndex >= agentDir_ospace.size()) neighborIndex = 0;

			double aAngle = atan2(agentDir_ospace[i].y(), agentDir_ospace[i].x()) - atan2(agentDir_ospace[neighborIndex].y(), agentDir_ospace[neighborIndex].x());
			if(aAngle < 0) aAngle += 2 * M_PI; // [0, 2PI]

			if(maxAngle < aAngle){
				maxAngle = aAngle;

				maxNeighborAngleIndex = neighborIndex;
				maxAngleIndex = i;
			}

//			ofLogNotice("Formation::findInteractionPosition")
//				<< "Angle(#" << sortedAgents[i]->getId() << ",#"
//				<< sortedAgents[neighborIndex]->getId() << ")=" << aAngle;
		}
	}

//	int maxAngleIndex = std::distance(agentAngle_ospace.begin(), std::max_element(agentAngle_ospace.begin(), agentAngle_ospace.end()));
	double rotAngle = maxAngle/2;

//	ofLogNotice("Formation::findInteractionPosition")
//		<< "Max angle found between Agent#" << sortedAgents[maxAngleIndex]->getId()
//		<< " and Agent#" << sortedAgents[maxNeighborAngleIndex]->getId() << " rotAngle=" << rotAngle;

	// Create interaction position vector from gravity center
	Rotation2Dd t(rotAngle);
	if(agentDir_ospace.size() > 2){
		Vector2d tmp = t.toRotationMatrix()*agentDir_ospace[maxAngleIndex].head<2>(); // Ignore Z
		interactionDirection << tmp.x(), tmp.y(), 0;
	}
	else{
		Vector2d tmp = t.toRotationMatrix()*agentDir_ospace[maxNeighborAngleIndex].head<2>(); // Ignore Z
		interactionDirection << tmp.x(), tmp.y(), 0;
	}

//	interactionDirection.normalize();

//	ofLogNotice("Formation::findInteractionPosition") << "Direction vector :" << std::endl << interactionDirection;

	// Compute mean distance from middle between gravity center and ospace center
	// TODO can be optimized and computed in previous loop
	double meanDistGCenter = 0;
	Vector3d meanCenter = (gCenter + this->_socialSpace->getCenter())/2;
	for(auto * a: sortedAgents)
	{
		meanDistGCenter += distance(a->getPosition(), meanCenter);
	}
	meanDistGCenter /= sortedAgents.size();

	interactionPosition = meanCenter + (interactionDirection * meanDistGCenter*2);

//	interactionDirection = this->_socialSpace->getCenter() - interactionPosition;
}

int Formation::isInFormation(unsigned int agentId) {
	if(this->getAgent(agentId)){
		return 1;
	}
	else{
		return 0;
	}
}

int Formation::isInFormation(Agent* agent) {
	return this->isInFormation(agent->getId());
}

std::vector<Agent*> Formation::initAgent(Agent* agent) {
	std::vector<Agent *> av;
	av.push_back(agent);
	return av;
}

// Getters & Setters
OSpace* Formation::getSocialSpace() const {
	return _socialSpace;
}

void Formation::setSocialSpace(OSpace* socialSpace) {
	_socialSpace = socialSpace;
}

double Formation::getInteractionPotential() const {
	return interactionPotential;
}

void Formation::setInteractionPotential(double interactionPotential) {
	this->interactionPotential = interactionPotential;
}

const Vector3d& Formation::getInteractionPosition() const {
	return interactionPosition;
}

void Formation::setInteractionPosition(const Vector3d& interactionPosition) {
	this->interactionPosition = interactionPosition;
}

const Vector3d& Formation::getInteractionDirection() const {
	return interactionDirection;
}

void Formation::setInteractionDirection(const Vector3d& interactionDirection) {
	this->interactionDirection = interactionDirection;
}
