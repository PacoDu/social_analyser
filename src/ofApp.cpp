#include "ofApp.h"
#include "config.h"

#undef Success // Eigen import clash with X11, dirty fix
#include "ofxMatrixEigen.h"
#include <cmath>

using namespace Eigen;

//void prog1(){
//	world = new World(5, 2.5, 600, 300, Vector3d(20,20,0), 0);
//	pop = new Population();
//
////	manager = new PopulationManager(world, "cocktail_party.json", "cocktail_party_gt.json");
////	manager = new PopulationManager(world, "coffee_break.json");
//
////	for(int i = 0; i < 3; i++){
////		Agent * a = new Agent(
////				world,
////				Point(rand()%10, rand()%10),
////				rand()%5,
////				i);
////		agents.push_back(a);
////		pop->pushAgent(a);
////	}
//
//	a0 = new Agent(Vector3d(2, 2, 0), 5.17, 0);
//	a1 = new Agent(Vector3d(4, 4, 0), 3.18, 1);
//	a2 = new Agent(Vector3d(3, 3, 0), 0.97, 2);
//
//	pop->pushAgent(a0);
//	pop->pushAgent(a1);
//	pop->pushAgent(a2);
//
//	map = new GridMap(world, pop, 0.5);
//	map->setPersonalSpaceEnabled(true);
//	map->setGroupSpaceEnabled(false);
//	map->setBorderEnabled(true);
//	map->update();
//
//	gd = new GroupDetector(pop);
//	gd->detect(); // TODO Strange bug, if detect is done befor map init map is miss located with an Y offset
////	manager->update(world);
//}

//void prog2(){
//	world = new World(5, 5, 600, 600, Vector3d(20,20,0), 0);
//	manager = new PopulationManager(world, "coffee_break.json", "coffee_break_gt.json");
//
//	map = new GridMap(world, manager->getPopulation(), 0.1);
//	map->setPersonalSpaceEnabled(true);
//	map->setGroupSpaceEnabled(false);
//	map->setBorderEnabled(true);
//	map->update();
//
////	gd = new GroupDetector(manager->getPopulation());
////	gd->detect();
//}

//	pop = new Population();

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
//		world = new World(5, 5, 600, 600, Vector3d(20,20,0), 0);
//		world = manager->getWorld();
//		pop = manager->getPopulation();
//		map = new GridMap(manager->getWorld(), manager->getPopulation(), 0.25);
//		map = new GridMap(world, pop, 0.25);
//		map->setPersonalSpaceEnabled(false);
//		map->setGroupSpaceEnabled(false);
//		map->setBorderEnabled(true);
//		map->update();

				//	a0 = new Agent(Vector3d(2.3, 4.4, 0), 5.37, 0);
				//	a1 = new Agent(Vector3d(3, 4, 0), 3.68, 1);
				//	a2 = new Agent(Vector3d(1.9, 3.8, 0), 0, 2);
				//	Agent * a3 = new Agent(Vector3d(4.1, 7.7, 0), 0, 3);
				//	Agent * a4 = new Agent(Vector3d(5.2, 7.3, 0), -3.8, 4);
				//	Agent * a5 = new Agent(Vector3d(6.3, 1.7, 0), 1.1, 5);
				//	Agent * a6 = new Agent(Vector3d(5.8, 2.3, 0), 0, 6);
				//	Agent * a7 = new Agent(Vector3d(6.3, 2.9, 0), -0.9, 7);
				//	Agent * a8 = new Agent(Vector3d(7.1, 1.9, 0), 2.5, 8);

				//	pop->pushAgent(a0);
				//	pop->pushAgent(a1);
				//	pop->pushAgent(a2);
				//	pop->pushAgent(a3);
				//	pop->pushAgent(a4);
				//	pop->pushAgent(a5);
				//	pop->pushAgent(a6);
				//	pop->pushAgent(a7);
				//	pop->pushAgent(a8);
				//
				//	map = new GridMap(world, pop, 0.1);
				//	map->setPersonalSpaceEnabled(true);
				//	map->setGroupSpaceEnabled(false);
				//	map->setBorderEnabled(false);
				//	map->update();

//					gd = new GroupDetector(manager->getPopulation());
//					gd = new GroupDetector(pop);
//					gd->detect(); // TODO Strange bug, if detect is done befor map init map is miss located with an Y offset
//	//	manager->update(world);
//	manager = new PopulationManager("coffee_break.json", "coffee_break_gt.json");


//--------------------------------------------------------------
void ofApp::setup(){

	robot = new Robot(Vector3d(0.5,0.5,0));

	world = new World(5 ,5, 600, 600, Vector3d(20,20,0), 0);

	manager = new PopulationManager(world);
	a0 = new Agent(Vector3d(1.5, 2.5, 0), 5.37, 0);
//	a1 = new Agent(Vector3d(3, 4, 0), 3.68, 1);
//	a2 = new Agent(Vector3d(4.5, 3, 0), 0.27, 2);

	manager->getPopulation()->pushAgent(a0);
//	manager->getPopulation()->pushAgent(a1);
//	manager->getPopulation()->pushAgent(a2);

	manager->update();

	socialPlanner = new SocialPlanner(manager, robot);
	udpServ = new UDPServer(UDP_SERVER_PORT, socialPlanner);
	server_thread = udpServ->spawn();
	gui = new Gui();
}

void ofApp::exit(){
	gui->exit();
}

//--------------------------------------------------------------
void ofApp::update(){
	socialPlanner->update();
	robot->update();
	manager->update();
	udpServ->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	manager->draw(world);
//	gui->draw();
	robot->draw(world);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	ofLogNotice("") << "__________________________________" << std::endl;
	if(key == OF_KEY_LEFT){
		ofLogNotice("DEBUG") << "Loading previous frame";
//		manager->previousFrame();
		manager->getPopulation()->getAgents()[mainIndex]->setX(manager->getPopulation()->getAgents()[mainIndex]->getX()-0.1);
//		manager->update(world);
//		pop->getAgents()[mainIndex]->setX(pop->getAgents()[mainIndex]->getX()-0.1);
	}
	else if(key == OF_KEY_RIGHT){
		ofLogNotice("DEBUG") << "Loading next frame";
//		manager->nextFrame();
		manager->getPopulation()->getAgents()[mainIndex]->setX(manager->getPopulation()->getAgents()[mainIndex]->getX()+0.1);
//		manager->update(world);
//		pop->getAgents()[mainIndex]->setX(pop->getAgents()[mainIndex]->getX()+0.1);
	}
	else if(key == OF_KEY_UP){
		manager->getPopulation()->getAgents()[mainIndex]->setY(manager->getPopulation()->getAgents()[mainIndex]->getY()-0.1);
//		pop->getAgents()[mainIndex]->setY(pop->getAgents()[mainIndex]->getY()-0.1);
	}
	else if(key == OF_KEY_DOWN){
		manager->getPopulation()->getAgents()[mainIndex]->setY(manager->getPopulation()->getAgents()[mainIndex]->getY()+0.1);
//		pop->getAgents()[mainIndex]->setY(pop->getAgents()[mainIndex]->getY()+0.1);
	}
	else if(key == 'z'){
		manager->getPopulation()->getAgents()[mainIndex]->setTheta(manager->getPopulation()->getAgents()[mainIndex]->getTheta()+0.1);
//		pop->getAgents()[mainIndex]->setTheta(pop->getAgents()[mainIndex]->getTheta()+0.1);
	}
	else if(key == 'a'){
		manager->getPopulation()->getAgents()[mainIndex]->setTheta(manager->getPopulation()->getAgents()[mainIndex]->getTheta()-0.1);
//		pop->getAgents()[mainIndex]->setTheta(pop->getAgents()[mainIndex]->getTheta()-0.1);
	}
	else if(key == 'e'){
		if(mainIndex < manager->getPopulation()->getAgents().size()-1) mainIndex++;
	}
	else if(key == 'r'){
		if(mainIndex > 0) mainIndex--;
	}
	else if(key == 'v'){
		Agent * newAgent = new Agent(Vector3d(0, 0, 0), 0.0, manager->getPopulation()->getAgents().size());
		manager->getPopulation()->pushAgent(newAgent);
//		pop->pushAgent(newAgent);
		mainIndex = manager->getPopulation()->getAgents().size()-1;
//		manager->runTest();
	}
	else if(key == 'u'){
//		gd->detect();
//		map->update();
		manager->update();
		socialPlanner->update();
//		udpServ->sendAll();
//		robot->update();
	}
	else if(key == 'i'){
//		map->findPath(map->getCell(0,0), map->getCell(6.9,6.9));
		manager->findInteraction();
	}
	else if(key == 'b'){
//		if(map->pathFinderNextStep() == 1)
//			map->constructPath();
	}

	ofLogNotice("DEBUG") << "Agent index = " << mainIndex;
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
