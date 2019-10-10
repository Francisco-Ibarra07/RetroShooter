#include "ofMain.h"
#include "ofxGui.h"

typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;

// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
//
class BaseObject {
public:
	BaseObject();
	ofVec2f trans, scale;
	float	rot;
	bool	bSelected;
	void setPosition(ofVec3f);
};

//  General Sprite class  (similar to a Particle)
//
class Sprite : public BaseObject {
public:
	Sprite();
	void draw(); // Draws sprite
	float age(); // Keeps track of how long the sprite has been around for
	void setImage(ofImage);
	float speed;    //   in pixels/sec
	ofVec3f velocity; // in pixels/sec
	ofImage image;
	ofRectangle hitbox;
	float birthtime; // elapsed time in ms
	float lifespan;  //  time in ms
	string name;
	bool haveImage;
	float width, height;  
};

//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteSystem  {
public:
	void add(Sprite);
	void remove(int);
	void update();
	void draw();
	int removeNear(ofVec3f point, float dist);
	vector<Sprite> sprites;
};


//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class Emitter: public BaseObject {
public:
	Emitter(SpriteSystem *);
	void draw();
	void start();
	void stop();
	void startSpriteCreation();
	void stopSpriteCreation();
	void setLifespan(float);
	void setVelocity(ofVec3f);
	void setChildImage(ofImage);
	void setChildSize(float w, float h) { childWidth = w; childHeight = h; }
	void setSpawnSound(ofSoundPlayer);
	void setImage(ofImage);
	void setRate(float);
	void update();
	SpriteSystem *sys;
	float rate;
	ofVec3f velocity;
	float lifespan;
	bool started;
	bool allowNewSpriteCreation;
	float lastSpawned;
	ofImage childImage;
	ofImage image;
	bool drawable;
	bool haveChildImage;
	bool haveImage;
	float width, height;
	float childWidth, childHeight;

	// Sound
	ofSoundPlayer spawnSound;
	bool haveSpawnSound;
};
