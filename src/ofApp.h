#pragma once

#include "ofMain.h"
#include "Player.h"
#include "Emitter.h"
#include "Stars.h"
#include "ParticleSystem.h"
#include "ParticleEmitter.h"

class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void checkCollisions();
		void particleExplosionAt(int x, int y);
		bool once = true;
	
		// Player
		Player player;
		Particle player_particle;

		// Star background
		Stars stars;

		// Music
		ofSoundPlayer music;

		// Game State
		string gameState;
		int score;

		// Font
		// GUI Related
		ofImage logo;
		ofTrueTypeFont title;
		ofTrueTypeFont subtitle;

		string UI_FONT = "fonts/SourceSansPro-Semibold.ttf";
		int UI_SIZE = 24;
		ofImage gui_time_background;
		ofImage gui_score_background;
		ofTrueTypeFont gui_time_font;
		ofTrueTypeFont gui_score_font;
		ofTrueTypeFont gui_fps_font;
		int gui_time;
		int gui_score;


		// Emitter properties
		Emitter *invaders;
		Emitter *invaders2;

		ofImage enemyImage;
		ofImage mothershipImage;
		bool move1 = true;
		bool move2 = false;

		// Turret Emitter
		Emitter *turretEmitter;
		ParticleEmitter explosionEmitter;
		bool bulletImageLoaded;
		ofImage bulletImage;
		ofSoundPlayer shootSound;
		ofSoundPlayer explosionSound;

		// Forces
		ImpulseRadialForce *radialForce;

		// ofxGui
		bool showGUI;
		ofxToggle showAimAssist;
		ofxToggle showSpriteHitboxes;
		ofxFloatSlider rate;
		ofxFloatSlider life;
		ofxVec3Slider velocity;
		ofxLabel screenSize;
		ofxPanel gui;
};
