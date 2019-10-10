#pragma once

#include "ofMain.h"
#include "Player.h"
#include "Emitter.h"

class ofApp : public ofBaseApp {
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

		// Player
		Player player;
		Player player2;

		// Star background
		vector<ofImage*> backgroundStars;
		vector<vector<int>> randNum;

		// Game State
		string gameState;

		// Font
		ofTrueTypeFont font;
		string startScreenText;

		// Emitter properties
		vector<Emitter*> enemyEmitterList;
		int numberOfEnemyEmitterList;

		// Turret Emitter
		Emitter* turretEmitter;
		bool bulletImageLoaded;
		ofImage bulletImage;
		ofSoundPlayer shootSound;

		// Mouse click - keeps track of which keys are being held down
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
