#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	std::string file = "synth.json";
	std::string file_gt = "synth_gt.json";

	// Parse the feature JSON
	bool parsingSuccessful = features.open(file);

	if (parsingSuccessful){
		ofLogNotice("ofApp::setup") << "Parsing features for frame #" << frameIndex;

		for (Json::ArrayIndex i = 0; i < features["features"][frameIndex].size(); ++i)
		{
			population.pushAgent(new Agent(
					features["features"][frameIndex][i][0].asInt(),
					features["features"][frameIndex][i][1].asDouble(),
					features["features"][frameIndex][i][2].asDouble(),
					features["features"][frameIndex][i][3].asDouble()
					));
		}

	}
	else{
		ofLogError("ofApp::setup")  << "Failed to parse features JSON" << std::endl;
	}

	// Parse the groundtruth JSON
	parsingSuccessful = groundThruth.open(file_gt);

	if (parsingSuccessful){
		ofLogNotice("ofApp::setup") << "Parsing ground truth for frame #" << frameIndex;

		for (Json::ArrayIndex i = 0; i < groundThruth["GTgroups"][frameIndex].size(); ++i)
		{
			std::vector<Agent*> group;
			for(Json::ArrayIndex j = 0; j < groundThruth["GTgroups"][frameIndex][i].size(); j++){
				group.push_back(population.getAgent(groundThruth["GTgroups"][frameIndex][i][j].asInt()));
			}

			population.pushFormation(
					new Formation(
						i,
						group[group.size()-1]->getX(),
						group[group.size()-1]->getY(),
						25.0f,
						40.0f,
						group)
				);
		}

	}
	else{
		ofLogError("ofApp::setup")  << "Failed to parse ground truth JSON" << std::endl;
	}


}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0xF9F9F9);

//	ofVec2f x_bound = population.getBoundX();
//	ofVec2f y_bound = population.getBoundY();

//	ofLogNotice("Population bounds: x("+ofToString(x_bound.x)+","+ofToString(x_bound.y)+") y("+ofToString(y_bound.x)+","+ofToString(y_bound.y)+")");

	population.draw(100, 100);

	std::stringstream ss;
	ss << "Frame #" << frameIndex;
	ofSetHexColor(0x2C291F);
	ofDrawBitmapString(ss.str(), 800, 14);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == OF_KEY_LEFT){
		if(frameIndex>0) frameIndex--;
	}
	else if(key == OF_KEY_RIGHT){
		if(frameIndex<features["features"].size()) frameIndex++;
	}

	population.clear();
//	population.clearAgents();
//	population.clearFormations();

	for (Json::ArrayIndex i = 0; i < features["features"][frameIndex].size(); ++i)
	{
		population.pushAgent(new Agent(
				features["features"][frameIndex][i][0].asDouble(),
				features["features"][frameIndex][i][1].asDouble(),
				features["features"][frameIndex][i][2].asDouble(),
				features["features"][frameIndex][i][3].asDouble()
				));
	}

	for (Json::ArrayIndex i = 0; i < groundThruth["GTgroups"][frameIndex].size(); ++i)
	{
		std::vector<Agent*> group;
		for(Json::ArrayIndex j = 0; j < groundThruth["GTgroups"][frameIndex][i].size(); j++){
			group.push_back(population.getAgent(groundThruth["GTgroups"][frameIndex][i][j].asInt()));
		}

		population.pushFormation(
				new Formation(
					i,
					group[group.size()-1]->getX(),
					group[group.size()-1]->getY(),
					25.0f,
					40.0f,
					group)
			);
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
