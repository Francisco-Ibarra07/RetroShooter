#include "Player.h"

void Player::setup(float _x, float _y) {
	x = _x;
	y = _y;
	image.load("images/player.png");
}

void Player::update() {
	if (up) y -= speed;
	if (down) y += speed;
	if (right) x += speed;
	if (left) x -= speed;
}

void Player::draw() {
	image.draw(x, y, width, height);
}

void Player::movement(int key, bool isMoving) {
	if (key == OF_KEY_UP || key == 'w') up = isMoving;
	if (key == OF_KEY_DOWN || key == 's') down = isMoving;
	if (key == OF_KEY_RIGHT || key == 'd') right = isMoving;
	if (key == OF_KEY_LEFT || key == 'a') left = isMoving;
}