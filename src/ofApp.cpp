#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	cam.initGrabber(320, 240);
	img.allocate(320, 240, OF_IMAGE_COLOR);
	shadow.allocate(320, 240, OF_IMAGE_COLOR);
	color.allocate(320, 240);
	finder.setup("haarcascade_frontalface_default.xml");
	fbo.allocate(320, 240, GL_RGBA32F_ARB);
	fbo.begin();
	ofClear(255, 255, 255, 0);
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
	cam.update();
	img.setFromPixels(cam.getPixels(), 320, 240, OF_IMAGE_COLOR);
	if (ofRandom(0, 10) < 4) {
		shadow = img;
	}
	finder.findHaarObjects(img);
}

//--------------------------------------------------------------
void ofApp::draw(){
	// ofBackground(80, 80, 80, 255);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
	// ofNoFill();
	// ofSetLineWidth(2);
	ofFill();

	fbo.begin();
    ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, 32);
	fbo.draw(20 - (cos(ofGetFrameNum() / 4) * 40), -ofRandom(2, 5));
	float h = fmodf(ofGetElapsedTimef()*10, 255);
	float s = 255;
	float v = 255 * cos(ofGetFrameNum() / 10);

	ofColor cc = ofColor::fromHsb(255 - h, 200, 128);
	ofSetColor(255 - (int)cc.r, 255 - (int)cc.g, 255 - (int)cc.b, ofRandom(16, 32));
	shadow.draw(2 - (cos(ofGetFrameNum() / 4) * 4), -ofRandom(2, 5));
	for (unsigned int i = 0; i < finder.blobs.size(); i++) {
		ofxCvBlob b = finder.blobs[i];
		ofRectangle r = b.boundingRect;
		//ofPoint p = b.centroid;
		ofPoint p = ofPoint(r.x, r.y);
		// int a = (r.width + r.height) / 3;
		int a = ofRandom(10, 50);

		h = fmodf((ofGetElapsedTimef() + (i * 1000)) * 10, 255);
		cc = ofColor::fromHsb(h, s, 255);
		ofSetColor((int)cc.r, (int)cc.g, (int)cc.b, ofRandom(32, 48));
		for (int j = 0; j < ofRandom(5, 50); j++) {
			ofCircle(ofRandom(p.x, p.x + r.width), ofRandom(p.y, p.y + r.height), a);
			ofCircle(ofRandom(p.x, p.x + r.width) - (r.width / 2), ofRandom(p.y, p.y + r.height) + (r.height * 1.5), a);
			ofCircle(ofRandom(p.x, p.x + r.width) + (r.width / 2), ofRandom(p.y, p.y + r.height) + (r.height * 1.5), a);
		}
	}
	fbo.end();
	// ofSetColor(255, 255, 255, 255);
	// shadow.draw(0, 0, 640, 480);
	ofSetColor(255, 255, 255, 255);
	img.draw(0, 0, 640, 480);
	ofSetColor(255, 255, 255, 255);
	fbo.draw(0, 0, 640, 480);
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
