#include "ofApp.h"

void ofApp::setup() {
	// Initial Project Setup
	ofSetWindowTitle("Project 1: Part 2 - A Vintage 2D Shooter Arcade Game - Francisco and Nhat");
	ofBackgroundHex(0x000000);

	// Game state setup
	gameState = "start";
	score = 0;

	// Load Font
	font.load("font/Squarewave.ttf", 64);
	startScreenText = "Start Screen (Press Space)";

	// Player setup
	float playerXPosition = ofGetWidth() / 2 - player.width / 2;
	float playerYPosition = ofGetHeight() - player.height * 4;
	player.setup(playerXPosition, playerYPosition);
	// player2.setup(playerXPosition, playerYPosition);

	// Star background
	stars.setup(25);

	// Emitter Setup
	// Load the bullet image. Exit if failure
	if (bulletImage.load("images/bullet.png")) bulletImageLoaded = true;
	enemyImage.load("images/enemy.png");

	// Sound Setup
	shootSound.load("sounds/shoot.wav");

	// Setup turret emitter
	turretEmitter = new Emitter(new SpriteSystem());
	turretEmitter->setPosition(ofVec3f(player.x, player.y, 0));
	turretEmitter->drawable = false;                // make emitter itself invisible
	turretEmitter->setChildImage(bulletImage);
	turretEmitter->setSpawnSound(shootSound);
	turretEmitter->start();

	// Setup enemy
	invaders = new Emitter(new SpriteSystem());
	invaders->setPosition(ofVec3f(ofGetWidth() / 2, 10 , 0));
	invaders->setChildImage(enemyImage);
	invaders->velocity.set(0, 400, 0);
	invaders->setLifespan(5000);
	invaders->setRate(1);
	invaders->setChildSize(20, 20);
	invaders->start();

	// Setup enemy
	invaders2 = new Emitter(new SpriteSystem());
	invaders2->setPosition(ofVec3f(ofGetWidth() / 2, ofGetHeight(), 0));
	invaders2->setChildImage(enemyImage);
	invaders2->velocity.set(0, 400, 0);
	invaders2->setLifespan(5000);
	invaders2->setRate(1);
	invaders2->setChildSize(20, 20);
	invaders2->start();
	
	// Setup gui
	gui.setup();
	gui.add(showAimAssist.setup("Aim", false));
	gui.add(rate.setup("rate", 4, 1, 10));
	gui.add(life.setup("life", 5, .1, 10));
	gui.add(velocity.setup("velocity", ofVec3f(100, -700, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
	showGUI = false;
}

void ofApp::update() {
	player.update();
	// player2.update();

	// Update Turret Emitter variables (space to shoot)
	player.isShooting ? turretEmitter->startSpriteCreation() : turretEmitter->stopSpriteCreation();
	// player2.isShooting ? turretEmitter->startSpriteCreation() : turretEmitter->stopSpriteCreation();

	// Shooting direction is between the circle and the mouse location
	ofVec3f shootingDirection = ofVec3f(ofGetMouseX() - player.x - player.width / 2, ofGetMouseY() - player.y - player.height / 2, 0);

	// Update turret properties
	turretEmitter->setRate(rate);
	turretEmitter->setLifespan(life * 1000);
	turretEmitter->setPosition(ofVec3f(player.x + player.width / 2, player.y + player.height / 2, 0));
	turretEmitter->setVelocity(shootingDirection);
	turretEmitter->update();

	// Update enemy mothership emitter properties
	ofVec3f v = invaders->velocity;
	invaders->setVelocity(ofVec3f(ofRandom(-v.y / 2, v.y / 2), v.y, v.z));
	invaders->update();

	ofVec3f v2 = -1 * invaders->velocity;
	invaders2->setVelocity(ofVec3f(ofRandom(-v2.y / 2, v2.y / 2), v2.y, v2.z));
	invaders2->update();

	// Check for collisions between the bullets
	checkCollisions();
}

void ofApp::draw() {
	if (gameState == "start") {
		ofSetColor(0xffffff);
		float textXPosition = (ofGetWidth() - font.stringWidth(startScreenText)) / 2;
		float textYPosition = (ofGetHeight() - font.stringHeight(startScreenText)) / 2;
		font.drawString(startScreenText, textXPosition, textYPosition);
	} else if (gameState == "game") {
		// Players
		player.draw();
		// player2.draw();
		turretEmitter->draw();
		
		// Invaders
		invaders->draw();
		invaders2->draw();
		
		// Star background
		stars.draw();
		
		// GUI 
		if (showGUI) gui.draw();
		if (showAimAssist) ofDrawLine(player.x + player.width / 2, player.y + player.height / 2, ofGetMouseX(), ofGetMouseY());
	}
}

void ofApp::checkCollisions() {
	float collisionDist = 25 + invaders->childHeight / 2;
	vector<int> removeMe;
	vector<int> removeMe2;
	int oldScore = 0;

	// Check collisions between bullet and invader 
	for (int i = 0; i < turretEmitter->sys->sprites.size(); i++) {
		oldScore = score;
		score += invaders->sys->removeNear(turretEmitter->sys->sprites[i].trans, collisionDist);
		if (score > oldScore) {
			oldScore = score;
			removeMe.push_back(i);
		}
		
		score += invaders2->sys->removeNear(turretEmitter->sys->sprites[i].trans, collisionDist);
		if (score > oldScore) {
			oldScore = score;
			removeMe.push_back(i);
		}
	}

	for (int index : removeMe)
		turretEmitter->sys->remove(index);
}

void ofApp::keyPressed(int key) {
	if (key == ' ') gameState = "game"; // Start to game screen
	if (key == 'h') showGUI = !showGUI; // Show/Hide GUI

	player.movement(key, true, { 'w', 'a', 's', 'd' });
	player.shoot(key, true, ' ');
	// player2.movement(key, true, { 'i', 'j', 'k', 'l' });
	// player2.shoot(key, true, ' ');
}

void ofApp::keyReleased(int key) {
	player.movement(key, false, { 'w', 'a', 's', 'd' });
	player.shoot(key, false, ' ');
	// player2.movement(key, false, { 'i', 'j', 'k', 'l' });
	// player2.shoot(key, false, ' ');
}

void ofApp::mousePressed(int x, int y, int button) {
	player.shoot(button, true, 0);
	// player2.shoot(button, true, 0);
}

void ofApp::mouseReleased(int x, int y, int button) {
	player.shoot(button, false, 0);
	// player2.shoot(button, false, 0);
}

// Unused openFrameworks methods
void ofApp::mouseMoved(int x, int y ) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
