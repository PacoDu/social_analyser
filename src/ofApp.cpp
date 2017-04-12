#include "ofApp.h"

#undef Success // Eigen import clash with X11, dirty fix
#include "ofxMatrixEigen.h"
#include <cmath>

using namespace Eigen;

//--------------------------------------------------------------
void ofApp::setup(){
	world = new World(10, 10, 600, 600, Vector3d(20,20,0), 0);
	pop = new Population();

//	manager = new PopulationManager(world, "cocktail_party.json", "cocktail_party_gt.json");
//	manager = new PopulationManager(world, "coffee_break.json");

//	for(int i = 0; i < 3; i++){
//		Agent * a = new Agent(
//				world,
//				Point(rand()%10, rand()%10),
//				rand()%5,
//				i);
//		agents.push_back(a);
//		pop->pushAgent(a);
//	}


//	ofLogNotice("DEBUG") << "Agent direction " << a0->getDirection();
	a0 = new Agent(Vector3d(2, 7, 0), 5.17, 0);
	a1 = new Agent(Vector3d(4, 6, 0), 3.18, 1);
	a2 = new Agent(Vector3d(2, 5, 0), 0.97, 2);

//	agents.push_back(a0);
//	agents.push_back(a1);
//	agents.push_back(a2);
//
	pop->pushAgent(a0);
	pop->pushAgent(a1);
	pop->pushAgent(a2);

	form = new Formation(pop->getAgents());
	pop->pushFormation(form);

	map = new GridMap(world, pop, 0.1);
//	gd = new GroupDetector(pop);

//	gd->detect();

//	manager->update(world);
}

//--------------------------------------------------------------
void ofApp::update(){
//	((OSpace*)form->getSocialSpace())->computeCenter();
//	((OSpace*)form->getSocialSpace())->sortAgents();
//	((OSpace*)form->getSocialSpace())->computeCentroids();
}

//--------------------------------------------------------------
void ofApp::draw(){
//	ofBackground(0xF9F9F9);

	world->draw();
//	a0->draw(world);
	//	form->draw(world);

	map->draw(world);
	pop->draw(world);

//	manager->draw(world);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == OF_KEY_LEFT){
//		manager->previousFrame();
//		manager->update(world);
		pop->getAgents()[mainIndex]->setX(pop->getAgents()[mainIndex]->getX()-1);
	}
	else if(key == OF_KEY_RIGHT){
//		manager->nextFrame();
//		manager->update(world);
		pop->getAgents()[mainIndex]->setX(pop->getAgents()[mainIndex]->getX()+1);
	}
	else if(key == OF_KEY_UP){
		pop->getAgents()[mainIndex]->setY(pop->getAgents()[mainIndex]->getY()-1);
	}
	else if(key == OF_KEY_DOWN){
		pop->getAgents()[mainIndex]->setY(pop->getAgents()[mainIndex]->getY()+1);
	}
	else if(key == 'z'){
		pop->getAgents()[mainIndex]->setTheta(pop->getAgents()[mainIndex]->getTheta()+0.2);
	}
	else if(key == 'e'){
		if(mainIndex+1 < pop->getAgents().size()) mainIndex++;
	}
	else if(key == 'r'){
		if(mainIndex-1 >= 0) mainIndex--;
	}

//	gd->detect();
	map->update();
	form->update();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
