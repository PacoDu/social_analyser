#include "ofMain.h"
#include "ofApp.h"
#include "udp_server.h"
#include "UDPServer.h"
#include "config.h"

//========================================================================
int main( ){
//	std::thread t1(udp_server_run, UDP_SERVER_PORT);

//	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
//	ofRunApp(new ofApp());

	UDPServer server(UDP_SERVER_PORT);

	server.run();
}
