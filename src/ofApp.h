#pragma once

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
		
		// Player 1
		StarShip player1;

		// Player 2 (if needed)
		StarShip player2;

		// Keeps track of which keys are down
		bool keyIsDown[255];
};
