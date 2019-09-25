#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	
	// Set up initial player 1 properties
	player1.xPosition = ofGetWidth() / 2;
	player1.yPosition = ofGetHeight() - 40;
	player1.width = 40;
	player1.height = 40;
	player1.speed = 10;
	player1.shootKey = ' ';
	ofSetBackgroundColor(ofColor::black);

	// Load the bullet image. Exit if failure
	if (bulletImage.load("images/space-invaders-ship-scaled.png")) {
		bulletImageLoaded = true;
	}
	else {
		ofLogFatalError("can't load image: images/space-invaders-ship-scaled.png");
		ofExit();
	}

	// Setup turret emitter
	turretEmitter = new Emitter(new SpriteSystem());
	turretEmitter->setPosition(ofVec3f(player1.xPosition, player1.yPosition, 0));
	turretEmitter->drawable = false;                // make emitter itself invisible
	turretEmitter->setChildImage(bulletImage);
	turretEmitter->start();

	// Setup gui
	gui.setup();
	gui.add(rate.setup("rate", 1, 1, 10));
	gui.add(life.setup("life", 5, .1, 10));
	gui.add(velocity.setup("velocity", ofVec3f(0, -700, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
	showGUI = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	// Cases for Player 1
	// Move up
	if (keyIsDown['w']) { 
		player1.yPosition -= player1.speed;
	}
	// Move down
	else if (keyIsDown['s']) { 
		player1.yPosition += player1.speed;
	}
	// Move right
	if (keyIsDown['d']) { 
		player1.xPosition += player1.speed;
	}
	// Move left
	else if (keyIsDown['a']) { 
		player1.xPosition -= player1.speed;
	}

	// Update Turret Emitter variables
	// If player presses the shoot key, then new "bullet" sprites can be spawned
	if (keyIsDown[player1.shootKey]) {
		turretEmitter->startSpriteCreation();
	}
	else {
		turretEmitter->stopSpriteCreation();
	}

	turretEmitter->setRate(rate);
	turretEmitter->setLifespan(life * 1000);
	turretEmitter->setPosition(ofVec3f(player1.xPosition, player1.yPosition, 0));
	turretEmitter->setVelocity(ofVec3f(velocity->x, velocity->y, velocity->z));
	turretEmitter->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	player1.draw();
	turretEmitter->draw();

	if (showGUI) {
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	keyIsDown[key] = true;

	// Show/Hide GUI
	if (key == 'h')
		showGUI = !showGUI;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	keyIsDown[key] = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
