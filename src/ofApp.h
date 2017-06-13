#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include <vector>

#include "PopulationManager.h"
#include "GaussianSpace.h"
#include "Agent.h"
#include "World.h"
#include "GridMap.h"
#include "GridCell.h"
#include "GroupDetector.h"
#include "Gui.h"
#include "Robot.h"
#include "SocialPlanner.h"
#include "UDPServer.h"

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
		void exit();

		void buttonPressed();
		


		Gui * gui;

		std::thread server_thread;
		UDPServer * udpServ;
		Robot * robot;
		SocialPlanner* socialPlanner;
		Population* pop;
		PopulationManager* manager;
		Formation* form;
		std::vector<Agent *> agents;
		Agent* a0;
		Agent* a1;
		Agent* a2;
		World* world;
		GridMap* map;
		GridCell* cell;
		GroupDetector* gd;
		unsigned int mainIndex = 0;
};
