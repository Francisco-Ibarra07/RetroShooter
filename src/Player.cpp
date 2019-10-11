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
	ofSetColor(0xffffff);
	image.draw(x, y, width, height);
}

void Player::movement(int key, bool isMoving, vector<char> movementKeys) {
	// {up, left, down, right}
	if (key == movementKeys[0]) up = isMoving;
	if (key == movementKeys[1]) left = isMoving;	// Rotate left
	if (key == movementKeys[2]) down = isMoving;	// Rotate right
	if (key == movementKeys[3]) right = isMoving;	// No movement
}

void Player::shoot(int button, bool _isShooting, int shootKey) {
	if (button == shootKey) isShooting = _isShooting;
}

bool Player::collides(ofRectangle hitbox) {

	bool x_range = (x < hitbox.x + hitbox.width) &&
		(x + width > hitbox.x);
	bool y_range = (y < hitbox.y + hitbox.height) &&
		(y + height > hitbox.y);

	return (x_range && y_range) ? true : false;
}
