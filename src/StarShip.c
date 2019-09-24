#include "StarShip.h"

void StarShip::draw() {
	ofDrawRectangle(xPosition, yPosition, width, height);
	hitbox = ofRectangle(xPosition, yPosition, width, height);
}