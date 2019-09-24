#include "ofApp.h"

void StarShip::draw() {
	ofDrawRectangle(xPosition, yPosition, width, height);
	hitbox = ofRectangle(xPosition, yPosition, width, height);
}


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
}

//--------------------------------------------------------------
void ofApp::draw(){
	player1.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	keyIsDown[key] = true;
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
