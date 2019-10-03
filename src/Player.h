#include "ofMain.h"

class Player {
	public:
		// TODO: Needs better image size logic
		float SIZE = 64;
		float width = SIZE;
		float height = SIZE;

		float x, y;
		ofImage image;

		float speed = 8;
		bool up, down, right, left;

		void setup(float x, float y);
		void update();
		void draw();

		void movement(int key, bool isMoving);
};