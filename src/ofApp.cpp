#include "ofApp.h"

void ofApp::setup() {
	// Initial Project Setup
	ofSetWindowTitle("Project 1: Part 1 - A Vintage 2D Shooter Arcade Game - Francisco and Nhat");
	ofBackgroundHex(0xdedede);

	// Game state setup
	gameState = "start";

	// Load Font
	font.load("Squarewave.ttf", 32);
	startScreenText = "Start Screen (Press Space)";

	// Player setup
	float playerXPosition = ofGetWidth() / 2 - player.width / 2;
	float playerYPosition = ofGetHeight() - player.height * 4;
	player.setup(playerXPosition, playerYPosition);

	// Emitter Setup
	// Load the bullet image. Exit if failure
	if (bulletImage.load("images/bullet.png")) bulletImageLoaded = true;

	// Sound Setup
	shootSound.load("sounds/shoot.wav");

	// Setup turret emitter
	turretEmitter = new Emitter(new SpriteSystem());
	turretEmitter->setPosition(ofVec3f(player.x, player.y, 0));
	turretEmitter->drawable = false;                // make emitter itself invisible
	turretEmitter->setChildImage(bulletImage);
	turretEmitter->setSpawnSound(shootSound);
	turretEmitter->start();

	// Setup gui
	gui.setup();
	gui.add(showAimAssist.setup("Aim", false));
	gui.add(rate.setup("rate", 8, 1, 10));
	gui.add(life.setup("life", 5, .1, 10));
	gui.add(velocity.setup("velocity", ofVec3f(100, -700, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
	showGUI = false;
}

void ofApp::update() {
	player.update();

	// Update Turret Emitter variables
	// If player presses the shoot key (Left mouse key), then new "bullet" sprites can be spawned
	mouseButtonIsDown[LEFT_CLICK] ? turretEmitter->startSpriteCreation() : turretEmitter->stopSpriteCreation();

	// Shooting direction is between the circle and the mouse location
	ofVec3f shootingDirection = ofVec3f(ofGetMouseX() - player.x, ofGetMouseY() - player.y, 0);

	turretEmitter->setRate(5);
	turretEmitter->setLifespan(1000);
	turretEmitter->setPosition(ofVec3f(player.x + player.width / 2, player.y + player.height / 2, 0));
	turretEmitter->setVelocity(shootingDirection);
	turretEmitter->update();
}

void ofApp::draw() {
	if (gameState == "start") {
		ofSetColor(ofColor::black);
		font.drawString(startScreenText, ofGetWidth() / 2 - font.stringWidth(startScreenText) / 2, ofGetHeight() / 2);
	} else if (gameState == "game") {
		player.draw();
		turretEmitter->draw();
	}

	if (showGUI) {
		gui.draw();
	}

	if (showAimAssist) {
		ofDrawLine(player.x, player.y, ofGetMouseX(), ofGetMouseY());
	}
}

void ofApp::keyPressed(int key) {
	player.movement(key, true);

	if (key == ' ')
		gameState = "game";

	// Show/Hide GUI
	if (key == 'h')
		showGUI = !showGUI;
}

void ofApp::keyReleased(int key) {
	player.movement(key, false);
}

void ofApp::mouseMoved(int x, int y ) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {
	mouseButtonIsDown[button] = true;
}
void ofApp::mouseReleased(int x, int y, int button) {
	mouseButtonIsDown[button] = false;
}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
