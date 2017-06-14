/*
 * Gui.h
 *
 *  Created on: Jun 6, 2017
 *      Author: paco
 */

#ifndef SRC_GUI_H_
#define SRC_GUI_H_

#include "ofxGui.h"

/**
 * @class Gui
 * @brief Graphical User Interface
 */
class Gui {
public:
	Gui();
	virtual ~Gui();

	void draw();
	void buttonPressed();
	void togglePressed(bool & pressed);
	void exit();

	ofxButton button;
	ofxToggle toggle;
	ofxPanel gui;
};

#endif /* SRC_GUI_H_ */
