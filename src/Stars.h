#include "ofMain.h"

class Stars {
	public:
		vector<ofImage*> backgroundStars;
		vector<vector<int>> randNum;

		void setup(int);
		void draw();
};