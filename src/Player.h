#include "ofMain.h"

class Player {
	public:
		float SIZE = 64;
		float width = SIZE;
		float height = SIZE;
		float speed = 8;
		bool isShooting = false;

		float x;
		float y;
		ofImage image;

		bool up;
		bool down;
		bool right;
		bool left;

		void setup(float, float);
		void update();
		void draw();

		void movement(int, bool, vector<char>);
		void shoot(int, bool, int);
};