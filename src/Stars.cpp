#include "Stars.h"

void Stars::setup(int amount) {
	ofImage* starPtr;
	int tempSize;
	for (int i = 0; i < amount; i++) {
		starPtr = new ofImage();
		starPtr->load("images/star.png");
		backgroundStars.push_back(starPtr);
		tempSize = rand() % 16 - 1;
		randNum.push_back({ rand() % ofGetWidth() - 8, rand() % ofGetHeight() - 8, rand() % 16 + 1, tempSize });
	}
}

void Stars::draw() {
	ofSetColor(0xffffff);
	for (int i = 0; i < backgroundStars.size(); i++) {
		backgroundStars[i]->draw(randNum[i][0], randNum[i][1], randNum[i][2], randNum[i][2]);
	}
}