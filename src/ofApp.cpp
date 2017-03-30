#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//	manager = new PopulationManager("coffee_break.json", "coffee_break_gt.json");
	a = new Agent(300, 300, 0.0, 1);
	c = new GaussianSpace(a);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
//	ofBackground(0xF9F9F9);
	c->draw();
	a->draw();

//	manager->draw(100, 100);
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
		a->setX(a->getX()-1);
	}
	else if(key == OF_KEY_RIGHT){
//		manager->nextFrame();
		a->setX(a->getX()+1);
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
