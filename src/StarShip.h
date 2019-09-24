#include "ofMain.h"

class StarShip {

	public:

		// Properties
		int xPosition;
		int yPosition;
		int width;
		int height;
		int speed;
		int shootKey;	// Key that will be used to allow this player to shoot
		ofRectangle hitbox;

		void draw();

};