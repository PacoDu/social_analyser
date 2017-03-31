#include "ofApp.h"
#include "Point.h"

//--------------------------------------------------------------
void ofApp::setup(){
//	manager = new PopulationManager("cocktail_party.json", "cocktail_party_gt.json");
	pop = new Population();
	world = new World(10, 10, 600, 600, Point(20,20), 0);

	for(int i = 0; i < 3; i++){
		Agent * a = new Agent(
				world,
				Point(rand()%10, rand()%10),
				6.70,
				i);
		agents.push_back(a);
		pop->pushAgent(a);
	}
//	a0 = new Agent(world, Point(5, 5), 6.89, 0);
//	a1 = new Agent(world, Point(2, 3), 6.89, 1);
//	a2 = new Agent(world, Point(4, 8), 6.89, 2);
//	c0 = new GaussianSpace(a0);
//	c1 = new GaussianSpace(a1);
//	c2 = new GaussianSpace(a2);
	form = new Formation(agents);
//	pop->pushAgent(a0);
//	pop->pushAgent(a1);
//	pop->pushAgent(a2);


//	pop->update(world);
//	c->compute(world);
//	manager->update(world);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
//	ofBackground(0xF9F9F9);
//	c->draw(world);
	world->draw();
	form->draw(world);
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
		agents[0]->setX(agents[0]->getX()-1);
	}
	else if(key == OF_KEY_RIGHT){
//		manager->nextFrame();
//		manager->update(world);
		agents[0]->setX(agents[0]->getX()+1);
	}
	else if(key == OF_KEY_UP){
		agents[0]->setY(agents[0]->getY()+1);
	}
	else if(key == OF_KEY_DOWN){
		agents[0]->setY(agents[0]->getY()-1);
	}
	else if(key == 'z'){
		agents[0]->setTheta(agents[0]->getTheta()+0.2);
	}
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
