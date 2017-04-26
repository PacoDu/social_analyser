/*
 * GridMap.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: paco
 */

#include "GridMap.h"
//#include "ofMain.h"

GridMap::GridMap(World* world, Population* pop,  double resolution):
		IdentifiedObject(), DrawnObject(), _population(pop), width(world->width), height(world->height), resolution(resolution) {
	assert(fmod(width*100,resolution*100) == 0);
	assert(fmod(height*100,resolution*100) == 0);

//	_map.resize((int)(this->height/this->resolution), std::vector<GridCell*>((int)(this->width/this->resolution), ));
	int cellId = 0;
	for(double i=0; i < this->height/this->resolution; i++){
		std::vector<GridCell*> tmp;
		for(double j=0; j < this->width/this->resolution; j++){
			tmp.push_back(new GridCell(
					resolution, 0,
					Vector3d(this->getX()+this->resolution*j, this->getY()+this->resolution*i, 0),
					cellId)
			);
			cellId++;
		}
		_map.push_back(tmp);
	}
	update();
	ofLogNotice("GridMap::GridMap") << "Initialized GridMap with " << cellId << " cells";
}

GridMap::~GridMap() {
	for(unsigned int i=0; i < this->height/this->resolution; i++){
		for(unsigned int j=0; j < this->width/this->resolution; j++){
			delete _map[i][j];
		}
	}
}

void GridMap::draw(World* world) {
//	Point pView = real_to_pixel(world, this->getPosition());
//	ofPushMatrix();
//		ofTranslate(pView.x, pView.y);
//		ofRotateZ(ofRadToDeg(this->getTheta()));
//	std::stringstream ss;

	for(unsigned int i=0; i < this->height/this->resolution; i++){
		for(unsigned int j=0; j < this->width/this->resolution; j++){
			_map[i][j]->draw(world);
//			ss << "GridCell #" << _map[i][j]->getId()
//					<< ": x = " << _map[i][j]->getX()
//					<< ", y = " << _map[i][j]->getY() << std::endl;
		}
	}


//	ofSetHexColor(0x2C291F);
//	ofDrawBitmapString(ss.str(), world->getX(), world->getY()+world->heightView+100);
//	ofPopMatrix();
}

void GridMap::compute() {
	minValue = INFINITY;
	maxValue = -INFINITY;
	for(unsigned int i=0; i < this->height/this->resolution; i++){
		for(unsigned int j=0; j < this->width/this->resolution; j++){
			double cellValue = 0;
			Vector3d testedPoint = _map[i][j]->getPosition();
			testedPoint.x() += _map[i][j]->getSize()/2;
			testedPoint.y() += _map[i][j]->getSize()/2;

			if(this->isPersonalSpaceEnabled()){
				for(unsigned int i = 0; i < this->_population->getAgents().size(); i++){
					cellValue += _population->getAgents()[i]->getSocialSpace()->phi(testedPoint);
				}
			}

			if(this->isGroupSpaceEnabled()){
				for(unsigned int i = 0; i < this->_population->getFormations().size(); i++){
					cellValue += _population->getFormations()[i]->getSocialSpace()->phi(testedPoint);
				}
			}

			_map[i][j]->setValue(cellValue);

			if(cellValue < minValue) minValue = cellValue;
			if(cellValue > maxValue) maxValue = cellValue;
		}
	}

	ofLogNotice("GridMap::compute") << "Social map computed min=" << minValue << ", max=" << maxValue;
}

void GridMap::normalize(){
	for(unsigned int i=0; i < this->height/this->resolution; i++){
		for(unsigned int j=0; j < this->width/this->resolution; j++){
			int newVal = (int)ofMap(_map[i][j]->getValue(), this->minValue, this->maxValue, 0, 255);
			_map[i][j]->setValue(newVal);

		}
	}
}

void GridMap::update() {
	compute();
	normalize();
}


std::vector<GridCell*> GridMap::neighbors(GridCell* cell, bool allowDiagonalMove) {
	//Get cell index
	int i = round((cell->getY()-this->getY())/this->resolution);
	int j = round((cell->getX()-this->getX())/this->resolution);

	std::vector<GridCell*> neighbors;

	//North neighbor
	if(i > 0)
		neighbors.push_back(_map[i-1][j]);
	//East neighbor
	if(j+1 < _map[i].size())
		neighbors.push_back(_map[i][j+1]);
	//South neighbor
	if(i+1 < _map.size())
		neighbors.push_back(_map[i+1][j]);
	//West neighbor
	if(j > 0)
		neighbors.push_back(_map[i][j-1]);

	if(allowDiagonalMove){
		//North-West neighbor
		if(i > 0 && j > 0)
			neighbors.push_back(_map[i-1][j-1]);
		//North-East neighbor
		if(j+1 < _map[i].size() && i > 0)
			neighbors.push_back(_map[i-1][j+1]);
		//South-East neighbor
		if(i+1 < _map.size() && j+1 < _map[i].size())
			neighbors.push_back(_map[i+1][j+1]);
		//South-West neighbor
		if(j > 0 && i+1 < _map.size())
			neighbors.push_back(_map[i+1][j-1]);
	}

	return neighbors;
}

// Manhattan distance (better for 4 movement on a grid)
double heuristicManhattanCostEstimate(GridCell* start, GridCell* end){
	return abs(start->getX() - end->getX()) + abs(start->getY() + end->getY());
}

// Diagonal distance (better for 8 movement on a grid)
double heuristicDiagonalCostEstimate(GridCell* start, GridCell* end){
	double dx = abs(start->getX() - end->getX());
	double dy = abs(start->getY() - end->getY());
	double D = 1; // Cost for moving forward
	double D2 = 5; // Cost for moving diagonally
	return D * (dx + dy) + (D2 - 2 * D) * min(dx, dy);
}



// A* algorithm
std::vector<GridCell*> GridMap::findPath(GridCell* startCell, GridCell* endCell){
//	typedef std::pair<double, GridCell*> VCell;
//
//	struct CompaireVCell
//	{
//	    bool operator()(VCell const& a, VCell const& b) const
//	    {
//	        return a.first > b.first;
//	    }
//	};
//
//	std::priority_queue<VCell, std::vector<VCell>, CompaireVCell > openNodesPQ;
//	std::map<GridCell*, GridCell*> cameFrom;
//	std::map<GridCell*, double> gScore;

	ofLogNotice("DEBUG") << "Computing path for Cell#" << startCell->getId() << " to Cell#" << endCell->getId();

	startCell->setGoal();
	endCell->setStart();

	openNodesPQ = std::priority_queue<VCell, std::vector<VCell>, CompaireVCell >();
	cameFrom.clear();
	gScore.clear();
	this->resetCellColor();

	this->startCell = startCell;
	this->endCell = endCell;

	openNodesPQ.push(std::make_pair(0, startCell));

	cameFrom[startCell] = startCell;
	gScore[startCell] = 0;

	int ret = 0;
//	while(!ret){
//		ret = pathFinderNextStep();
//	}

	std::vector<GridCell*> pathFound;

	if(ret == 1)
		pathFound = constructPath();

	return pathFound;

//
//	while(!openNodesPQ.empty()){
//		// Get highest priority cell (lowest score)
//		ofLogNotice("DEBUG") << "Processing Cell#" << openNodesPQ.top().second->getId() << " value=" << openNodesPQ.top().second->getValue() ;
//		GridCell* currentNode = openNodesPQ.top().second;
//
//		if(currentNode == endCell){
//			ofLogNotice("DEBUG") << "Goal reached";
//			break;
//		}
//
//		// Find neighbor
//		std::vector<GridCell*> neighbors = this->neighbors(currentNode);
//		for(auto * nextNode: neighbors){
//			double newCost = gScore[currentNode] + nextNode->getValue();
//
//			// nextNode not in gScore or newCost < gScore
//			// nextNode haven't been evaluated or newCost is lower than previous evaluation (better path)
//			// gScore.find(nextNode) == gScore.end() ||
//			if( gScore.find(nextNode) == gScore.end()
//					|| (gScore.find(nextNode) != gScore.end() && newCost < gScore[nextNode])){
//
//				gScore[nextNode] = newCost;
//				double priority = newCost + heuristicDiagonalCostEstimate(nextNode, endCell);
//
//				openNodesPQ.push(std::make_pair(priority, nextNode));
//				cameFrom[nextNode] = currentNode;
//
//				nextNode->setAStarScore(newCost);
//
//				ofLogNotice("DEBUG") << "Node#" << nextNode->getId() << " score=" << newCost << " priority=" << priority;
//			}
//		}
//
//		openNodesPQ.pop();
//	}
//
//	// Construct path
//	this->deselectCells();
//	std::vector<GridCell*> pathFound;
//	GridCell* currentCell = endCell;
//
//	pathFound.push_back(currentCell);
//
//	while(currentCell != startCell){
//		currentCell = cameFrom[currentCell];
//		pathFound.push_back(currentCell);
//		currentCell->setCellSelected();
//	}
//
//	return pathFound;
}



GridCell* GridMap::getCell(int cellId) {
	for(auto mapRow: _map){
		for(auto * cell: mapRow){
			if(cell->getId() == cellId)
				return cell;
		}
	}
	return nullptr;
}

void GridMap::deselectCells() {
	for(auto mapRow: _map){
		for(auto * cell: mapRow){
			cell->setCellSelected(false);
		}
	}
}

void GridMap::resetCellColor() {
	for(auto mapRow: _map){
		for(auto * cell: mapRow){
			cell->setCellSelected(false);
			cell->setFrontier(false);
			cell->setProcessed(false);
		}
	}
}


bool GridMap::isGroupSpaceEnabled() const {
	return groupSpaceEnabled;
}

void GridMap::setGroupSpaceEnabled(bool groupSpaceEnabled) {
	this->groupSpaceEnabled = groupSpaceEnabled;
}

bool GridMap::isPersonalSpaceEnabled() const {
	return personalSpaceEnabled;
}

void GridMap::setPersonalSpaceEnabled(bool personalSpaceEnabled) {
	this->personalSpaceEnabled = personalSpaceEnabled;
}

bool GridMap::isBorderEnabled() const {
	return borderEnabled;
}

// Return -1 if goal is not reachable, 0 if nextstep is needed, 1 if goal is reached
int GridMap::pathFinderNextStep() {
	if(!openNodesPQ.empty()){
		// Get highest priority cell (lowest score)
		ofLogNotice("DEBUG") << "Processing Cell#"
				<< openNodesPQ.top().second->getId()
				<< " priority=" << openNodesPQ.top().first
				<< " value=" << openNodesPQ.top().second->getValue() ;

		GridCell* currentNode = openNodesPQ.top().second;
		openNodesPQ.pop();
		currentNode->setFrontier(false);
		currentNode->setProcessed();

		if(currentNode == endCell){
			return 1;
		}

		// Find neighbor
		std::vector<GridCell*> neighbors = this->neighbors(currentNode, false);
		for(auto * nextNode: neighbors){
			double newCost = gScore[currentNode] + currentNode->getValue();

			// nextNode not in gScore or newCost < gScore
			// nextNode haven't been evaluated or newCost is lower than previous evaluation (better path)
			if( gScore.find(nextNode) == gScore.end() || newCost < gScore[nextNode]){

				gScore[nextNode] = newCost;
				double priority = newCost + heuristicManhattanCostEstimate(nextNode, endCell);

				openNodesPQ.push(std::make_pair(priority, nextNode));
				cameFrom[nextNode] = currentNode;

				nextNode->setAStarScore(newCost);

				nextNode->setFrontier();

				ofLogNotice("DEBUG") << "Node#" << nextNode->getId() << " score=" << newCost << " priority=" << priority;
			}
		}
	}
	else{
		ofLogNotice("DEBUG") << "Error goal unreachable";
		return -1;
	}


	int i = 0;
	for(auto * cell: _map[0]){
		if(cell->isProcessed())
			i++;
	}

	ofLogNotice("DEBUG") << "_map[0] => " << i << " Cells processed.";

	return 0;
}

std::vector<GridCell*> GridMap::constructPath() {
	// Construct path
	this->deselectCells();
	std::vector<GridCell*> pathFound;
	GridCell* currentCell = endCell;

	pathFound.push_back(currentCell);

	while(currentCell != startCell){
		currentCell = cameFrom[currentCell];
		pathFound.push_back(currentCell);
		currentCell->setCellSelected();
	}

	return pathFound;
}

void GridMap::setBorderEnabled(bool borderEnabled) {
	for(unsigned int i=0; i < this->height/this->resolution; i++){
		for(unsigned int j=0; j < this->width/this->resolution; j++){
			_map[i][j]->setBorderEnabled(borderEnabled);
		}
	}
	this->borderEnabled = borderEnabled;
}
