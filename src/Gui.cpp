/*
 * Gui.cpp
 *
 *  Created on: Jun 6, 2017
 *      Author: paco
 */

#include "Gui.h"

Gui::Gui() {
	// TODO Auto-generated constructor stub
	button.addListener(this, &Gui::buttonPressed);
	toggle.addListener(this, &Gui::togglePressed);

	gui.setup();
	gui.add(button.setup("button"));
	gui.add(toggle.setup("toggle"));
}

Gui::~Gui() {
	// TODO Auto-generated destructor stub
}

void Gui::buttonPressed() {
	ofLogNotice("Button") << "Pressed";
}

void Gui::draw() {
	gui.draw();
}

void Gui::exit() {
	button.removeListener(this, &Gui::buttonPressed);
}

void Gui::togglePressed(bool & pressed) {
	ofLogNotice("Toggle") << "Pressed";
}
