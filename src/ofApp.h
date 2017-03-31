#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include <vector>

#include "PopulationManager.h"
#include "GaussianSpace.h"
#include "Agent.h"
#include "Point.h"
#include "World.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		Population* pop;
		PopulationManager* manager;
		Formation* form;
		std::vector<Agent *> agents;
		Agent* a0;
		Agent* a1;
		Agent* a2;
		World* world;
};
