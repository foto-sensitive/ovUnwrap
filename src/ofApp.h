

/*Created by Robert Pavlovskis on 11/07/2015
This is example shows how you can unwrap and navigate 360? video and image.
Drag & drop videos or  pictures  onto the window to unwrap 360? media.
Drag the mouse across the screen to look around.*/


#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	~ofApp();
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	//Unwraps 360? media
	void unwrap();

	//Renders the sphere
	GLUquadricObj *quadric;
	//Adds camera and controls
	ofEasyCam cam;

	//Path to your media
	string path;
	ofImage img;
	ofVideoPlayer vid;
	//Determines video or image
	bool vidFormat;

};
