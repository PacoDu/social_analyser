#include "ofApp.h"
#include "Point.h"

//--------------------------------------------------------------
void ofApp::setup(){
	world = new World(10, 10, 600, 600, Point(20,20), 0);
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
	a0 = new Agent(world, Point(2, 7), 11.4, 0);
	a1 = new Agent(world, Point(6, 4), 2.6, 1);
	a2 = new Agent(world, Point(2, 3), 13.2, 2);
	agents.push_back(a0);
	pop->pushAgent(a0);
	agents.push_back(a1);
	pop->pushAgent(a1);
	agents.push_back(a2);
	pop->pushAgent(a2);
	form = new Formation(agents);
	pop->pushFormation(form);
	pop->update(world);
//	pop->update(world);
//	c->compute(world);
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
//	c->draw(world);
	world->draw();
//	form->draw(world);
//	c->draw(world);
//	a->draw(world);
	pop->draw(world);


//	manager->draw(world);
//	c.draw(100,100);
//	std::stringstream ss;
//	ss << "Frame #" << manager->getFrameIndex();
//	ofSetHexColor(0x2C291F);
//	ofDrawBitmapString(ss.str(), 800, 14);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == OF_KEY_LEFT){
//		manager->previousFrame();
//		manager->update(world);
		agents[mainIndex]->setX(agents[mainIndex]->getX()-1);
	}
	else if(key == OF_KEY_RIGHT){
//		manager->nextFrame();
//		manager->update(world);
		agents[mainIndex]->setX(agents[mainIndex]->getX()+1);
	}
	else if(key == OF_KEY_UP){
		agents[mainIndex]->setY(agents[mainIndex]->getY()-1);
	}
	else if(key == OF_KEY_DOWN){
		agents[mainIndex]->setY(agents[mainIndex]->getY()+1);
	}
	else if(key == 'z'){
		agents[mainIndex]->setTheta(agents[mainIndex]->getTheta()+0.2);
	}
	else if(key == 'e'){
		if(mainIndex+1 < agents.size()) mainIndex++;
	}
	else if(key == 'r'){
		if(mainIndex-1 >= 0) mainIndex--;
	}

	pop->update(world);
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
