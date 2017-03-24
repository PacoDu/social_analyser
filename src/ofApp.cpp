#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	std::string file = "coffee_break.json";

	// Parse the JSON
	bool parsingSuccessful = json.open(file);

	if (parsingSuccessful){
//		ofLogNotice("ofApp::setup") << json.getRawString();

		for (Json::ArrayIndex i = 0; i < json["features"][j].size(); ++i)
		{
			population.push(new Person(
					json["features"][0][i][0].asDouble(),
					json["features"][0][i][1].asDouble(),
					json["features"][0][i][2].asDouble(),
					json["features"][0][i][3].asDouble()
					));
		}

	}
	else{
		ofLogError("ofApp::setup")  << "Failed to parse JSON" << std::endl;
	}


}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0xF9F9F9);

	ofVec2f x_bound = population.getBoundX();
	ofVec2f y_bound = population.getBoundY();

//	ofLogNotice("Population bounds: x("+ofToString(x_bound.x)+","+ofToString(x_bound.y)+") y("+ofToString(y_bound.x)+","+ofToString(y_bound.y)+")");

	population.draw(-x_bound.x + 100,-y_bound.x + 100);

	std::stringstream ss;
	ss << "Frame #" << j;
	ofSetHexColor(0x2C291F);
	ofDrawBitmapString(ss.str(), 800, 14);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == OF_KEY_LEFT){
		if(j>0) j--;
	}
	else if(key == OF_KEY_RIGHT){
		if(j<json["features"].size()) j++;
	}

	population.clear();
	for (Json::ArrayIndex i = 0; i < json["features"][j].size(); ++i)
	{
		population.push(new Person(
				json["features"][j][i][0].asDouble(),
				json["features"][j][i][1].asDouble(),
				json["features"][j][i][2].asDouble(),
				json["features"][j][i][3].asDouble()
				));
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
