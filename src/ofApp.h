#pragma once

#include "ofMain.h"
#include "Emitter.h"
#include "StarShip.h"

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
		
		// Emitter properties
		vector<Emitter*> enemyEmitterList;
		int numberOfEnemyEmitterList;


		// Turret Emitter
		Emitter* turretEmitter;
		bool bulletImageLoaded;
		ofImage bulletImage;

		// Player 1
		StarShip player1;

		// Player 2 (if needed)
		StarShip player2;

		// Keeps track of which keys are being held down
		bool keyIsDown[255];
		bool mouseButtonIsDown[3];
		typedef enum { LEFT_CLICK, SCROLL_CLICK, RIGHT_CLICK } Mouse;

		// ofxGui
		bool showGUI;
		ofxToggle showAimAssist;
		ofxFloatSlider rate;
		ofxFloatSlider life;
		ofxVec3Slider velocity;
		ofxLabel screenSize;
		ofxPanel gui;
};
