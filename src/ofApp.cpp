

/*Created by Robert Pavlovskis on 11/07/2015
This is example shows how you can unwrap and navigate 360° video and image.
Drag & drop videos or  pictures  onto the window to unwrap 360° media. 
Drag the mouse across the screen to look around.*/


#include "ofApp.h"

//-------------------------------------------------------------
ofApp::~ofApp() {

}

//--------------------------------------------------------------
void ofApp::setup(){

	//Load Demo Texture
	path = "ocean.bmp";
	vid.loadMovie(path);
	vid.play();

	//Prepare quadric for sphere
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	//Place camera inside sphere at 0,0,0
	cam.setAutoDistance(false);

	//Working with video
	vidFormat = true;
}

//--------------------------------------------------------------
void ofApp::update(){
	//Updates if working with video
	if(vidFormat)
	vid.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	//Place camera inside the sphere
	cam.begin();
	//Map 360° texture to sphere
	unwrap();
	cam.end();
	
	//GUI
	ofSetColor(0, 130);
	ofRect(10, 10, 357, 73);
	ofSetColor(255);
	ofDrawBitmapString("Drag & drop videos and  pictures  onto the", 20, 30);
	ofDrawBitmapString("window to unwrap 360° media. Drag the mouse", 20, 50);
	ofDrawBitmapString("across the screen to look around.", 20, 70);
	ofDrawBitmapString(path, 20, ofGetHeight()*0.97);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::dragEvent(ofDragInfo info) {
    
	//Get dragged file path
	path = info.files[0];
	//Get extension
	ofFile file(ofToDataPath(path));

	//Loads movie if video is dropped
	if (file.getExtension() == "avi") {
		vid.loadMovie(info.files[0]);
		vid.play();
		vidFormat = true;
	}

	//Loads image if picture is dropped
	if (file.getExtension() == "bmp" || file.getExtension() == "jpg" || file.getExtension() == "png") {
		img.loadImage(info.files[0]);
		vidFormat = false;
	}
}

//--------------------------------------------------------------
void ofApp::unwrap() {

	ofSetColor(255, 255, 255);

	//Determines weather to bind video or image
	if(vidFormat)
	vid.getTextureReference().bind();
	else img.getTextureReference().bind();

	ofPushMatrix();
	ofRotateX(90);

	//Apply operations to texture matrix
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();


	//Determine if texture is a video or image
	if (vidFormat)
	//Scale texture to sphere
	ofScale(vid.getWidth(), vid.getHeight());
	else ofScale(img.getWidth(), img.getHeight());

	//Apply operations to model matrix
	glMatrixMode(GL_MODELVIEW);

	//Enable depth comparisons, needed so you see the correct planes from your perspective
	glEnable(GL_DEPTH_TEST); 
    //Disables the use of ARB textures, has to be disabled for drawing sphere
	ofDisableArbTex(); 

	gluSphere(quadric, 200, 100, 100);

	//Disables depth comparisons, needed for performing texture operations
	glDisable(GL_DEPTH_TEST);
    //Enables the use of ARB textures, needed to bind textures
	ofEnableArbTex(); //needed for textures to work with gluSphe

   //Apply operations to texture matrix
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	//Determines weather to unbind video or image
	if (vidFormat)
	vid.getTextureReference().unbind();
	else img.getTextureReference().unbind();

	ofPopMatrix();
}
