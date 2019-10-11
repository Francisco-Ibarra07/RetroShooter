#include "ofApp.h"

void ofApp::setup() {
	// Initial Project Setup
	ofSetWindowTitle("Project 1: Part 2 - A Vintage 2D Shooter Arcade Game - Francisco and Nhat");
	ofBackgroundHex(0x000000);

	// Game state setup
	gameState = "start";
	score = 0;

	// Font setup
	font.load("font/Squarewave.ttf", 64);
	scoreFont.load("font/Squarewave.ttf", 30);
	startScreenText = "Start Screen (Press Space)";

	// Images setup
	enemyImage.load("images/enemy.png");
	bulletImage.load("images/bullet.png");
	mothershipImage.load("images/boss.png");

	// Sounds setup
	shootSound.load("sounds/shoot.wav");
	explosionSound.load("sounds/explosion.wav");
	music.load("sounds/music.wav");
	music.setLoop(true);
	music.play();

	// Player setup
	float playerXPosition = (ofGetWidth() - player.width) / 2;
	float playerYPosition = (ofGetHeight() - player.height) / 2;
	player.setup(playerXPosition, playerYPosition);

	// Star background
	stars.setup(25);

	// Setup turret emitter
	turretEmitter = new Emitter(new SpriteSystem());
	turretEmitter->setPosition(ofVec3f(player.x, player.y, 0));
	turretEmitter->drawable = false;                // make emitter itself invisible
	turretEmitter->setChildImage(bulletImage);
	turretEmitter->setSpawnSound(shootSound);
	turretEmitter->start();

	// Setup enemy (top)
	invaders = new Emitter(new SpriteSystem());
	invaders->setPosition(ofVec3f(rand() % ofGetWidth(), mothershipImage.getHeight(), 0));
	invaders->setChildImage(enemyImage);
	invaders->velocity.set(0, 400, 0);
	invaders->setLifespan(5000);
	invaders->setRate(1);
	invaders->setChildSize(20, 20);
	invaders->setImage(mothershipImage);
	invaders->start();

	// Setup enemy (bottom)
	invaders2 = new Emitter(new SpriteSystem());
	invaders2->setPosition(ofVec3f(rand() % ofGetWidth(), ofGetHeight() - mothershipImage.getHeight(), 0));
	invaders2->setChildImage(enemyImage);
	invaders2->velocity.set(0, 400, 0);
	invaders2->setLifespan(5000);
	invaders2->setRate(1);
	invaders2->setChildSize(20, 20);
	invaders2->setImage(mothershipImage);
	invaders2->start();
	
	// Setup GUI
	gui.setup();
	gui.add(showAimAssist.setup("Aim", false));
	gui.add(rate.setup("rate", 4, 1, 10));
	gui.add(life.setup("life", 5, .1, 10));
	gui.add(velocity.setup("velocity", ofVec3f(100, -700, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
	showGUI = false;
}

void ofApp::update() {
	player.update();

	// Update Turret Emitter variables (space to shoot)
	player.isShooting ? turretEmitter->startSpriteCreation() : turretEmitter->stopSpriteCreation();

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

	// Enemies side to side movement
	if (move1) {
		invaders->setPosition(ofVec3f(invaders->trans.x + 10, invaders->trans.y, 0));
		if (invaders->trans.x > ofGetWidth()) move1 = !move1;
	} else {
		invaders->setPosition(ofVec3f(invaders->trans.x - 10, invaders->trans.y, 0));
		if (invaders->trans.x < 0) move1 = !move1;
	}
	if (move2) {
		invaders2->setPosition(ofVec3f(invaders2->trans.x + 10, invaders2->trans.y, 0));
		if (invaders2->trans.x > ofGetWidth()) move2 = !move2;
	} else {
		invaders2->setPosition(ofVec3f(invaders2->trans.x - 10, invaders2->trans.y, 0));
		if (invaders2->trans.x < 0) move2 = !move2;
	}
}

void ofApp::draw() {
	if (gameState == "start") {

		// Stop all emitters
		turretEmitter->stop();
		invaders->stop();
		invaders2->stop();

		// Clear all sprites from emitters
		invaders->sys->sprites.clear();
		invaders2->sys->sprites.clear();
		turretEmitter->sys->sprites.clear();

		// Reset player position
		player.x = ofGetWidth() / 2;
		player.y = ofGetHeight() / 2;

		// Start screen
		ofSetColor(0xffffff);
		float textXPosition = (ofGetWidth() - font.stringWidth(startScreenText)) / 2;
		float textYPosition = (ofGetHeight() - font.stringHeight(startScreenText)) / 2;
		font.drawString(startScreenText, textXPosition, textYPosition);
	} else if (gameState == "game") {

		if (once) {
			turretEmitter->start();
			invaders->start();
			invaders2->start();
			once = false;
		}

		// Game screen
		// Stars for background
		stars.draw();

		// Player
		player.draw();
		turretEmitter->draw();
		
		// Invaders
		invaders->draw();
		invaders2->draw();
		
		// Stars for background
		stars.draw();
		
		// Draw player score
		string scoreString = "Score: " + to_string(score);
		float textXPosition = font.stringWidth(scoreString);
		float textYPosition = font.stringHeight(scoreString);
		scoreFont.drawString(scoreString, textXPosition, textYPosition);

		// GUI 
		if (showGUI) gui.draw();
		if (showAimAssist) ofDrawLine(player.x + player.width / 2, player.y + player.height / 2, ofGetMouseX(), ofGetMouseY());
	
	} else if (gameState == "gameover") {

		// Stop all emitters
		turretEmitter->stop();
		invaders->stop();
		invaders2->stop();

		// Clear all sprites from emitters
		invaders->sys->sprites.clear();
		invaders2->sys->sprites.clear();
		turretEmitter->sys->sprites.clear();

		// Reset player position
		player.x = ofGetWidth() / 2;
		player.y = ofGetHeight() / 2;

		// Reset score
		score = 0;

		ofSetColor(0xffffff);
		float textXPosition = (ofGetWidth() - font.stringWidth("You Lose")) / 2;
		float textYPosition = (ofGetHeight() - font.stringHeight("You Lose")) / 2;
		font.drawString("You Lose", textXPosition, textYPosition);
		font.drawString("Press Space to try again", textXPosition, textYPosition + font.stringHeight("You Lose"));
		once = true;
	}
}

void ofApp::checkCollisions() {
	float collisionDist = 25 + invaders->childHeight / 2;
	vector<int> removeMe;
	int oldScore = 0;
	ofRectangle invaderHitbox;

	// Check collisions between bullet and invader 
	for (int i = 0; i < turretEmitter->sys->sprites.size(); i++) {
		oldScore = score;
		score += invaders->sys->removeNear(turretEmitter->sys->sprites[i].trans, collisionDist);
		if (score > oldScore) {
			oldScore = score;
			explosionSound.play();
			removeMe.push_back(i);
		}
		
		score += invaders2->sys->removeNear(turretEmitter->sys->sprites[i].trans, collisionDist);
		if (score > oldScore) {
			oldScore = score;
			explosionSound.play();
			removeMe.push_back(i);
		}
	}

	// Remove any bullet sprites that hit an invader
	for (int index : removeMe)
		turretEmitter->sys->remove(index);

	// Check if the player hit an invader
	for (int i = 0; i < invaders->sys->sprites.size(); i++) {
		if (player.collides(invaders->sys->sprites[i].hitbox)) {
			gameState = "gameover";
			return;
		}
	}

	for (int i = 0; i < invaders2->sys->sprites.size(); i++) {
		if (player.collides(invaders2->sys->sprites[i].hitbox)) {
			gameState = "gameover";
			return;
		}
	}
}

void ofApp::keyPressed(int key) {
	if (key == ' ') gameState = "game"; // Start to game screen
	if (key == 'h') showGUI = !showGUI; // Show/Hide GUI

	// Configure player controls (move: wasd, shoot: spacebar)
	if (gameState == "game") {
		player.movement(key, true, { 'w', 'a', 's', 'd' });
		player.shoot(key, true, ' ');
	}
}

void ofApp::keyReleased(int key) {
	// Configure player controls (move: wasd, shoot: spacebar)
	player.movement(key, false, { 'w', 'a', 's', 'd' });
	player.shoot(key, false, ' ');
}

void ofApp::mousePressed(int x, int y, int button) {
	// Configure player controls (shoot: left click)
	player.shoot(button, true, 0);
}

void ofApp::mouseReleased(int x, int y, int button) {
	// Configure player controls (shoot: left click)
	player.shoot(button, false, 0);
}

// Unused openFrameworks methods
void ofApp::mouseMoved(int x, int y ) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
